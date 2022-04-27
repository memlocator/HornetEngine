#include "GlowingSceneOperation.h"

extern "C" {
#include <math.h>
}

#include "Graphics.h"
#include "Textures.h"
#include "Constants.h"
#include "Light.h"
#include "HDRColorCorrectionOperation.h"

#define WATER_MAT_SIDE_LENGTH 6

// ADDED
namespace HelperFunctions
{
  float F(float x, float y)
  {
    return cosf(x) + sinf(y) / (x + y + 1);
  }

  float CalculateAmn(int m, int n, float a, float b, int x_resolution, int y_resolution)
  {
    float Amn = static_cast<float>(4) / (a * b);

    float doubleSum = 0;

    float x, y, dX, dY, sinTerm;

    dX = a / x_resolution;
    dY = b / y_resolution;

    for (int i = 0; i < x_resolution; ++i)
    {
      for (int j = 0; j < y_resolution; ++j)
      {
        x = i * a / x_resolution;
        y = j * b / y_resolution;
        sinTerm = sinf(m * PI * x / a);

        doubleSum += F(x, y) * sinTerm * sinTerm * dX * dY;
      }
    }

    Amn *= doubleSum;

    return Amn;
  }

  float CalculateKmn(int m, int n, float a, float b)
  {
    return PI * sqrt(static_cast<float>(m * m) / (b * b) + static_cast<float>(n * n) / (b * b));
  }
}

namespace GraphicsEngine
{
	void GlowingSceneOperation::Initialize()
	{
		RenderOperation::Initialize();

		auto camera = Engine::Create<Camera>();

		ShadowCamera = camera;

		camera->SetParent(This.lock());

		//SetTicks(true);
	}

	void GlowingSceneOperation::Configure(int width, int height, const std::shared_ptr<Scene>& scene, const std::shared_ptr<FrameBuffer>& output)
	{
		Output = output;
		std::shared_ptr<DrawSceneOperation> sceneDraw = Engine::Create<DrawSceneOperation>();
		sceneDraw->CurrentScene = scene;
		sceneDraw->SetParent(This.lock());

		SceneDraw = sceneDraw;

		/***************************************************************************************************
		Water Buffer Config Start
		***************************************************************************************************/

		int waterWidth = 2048;
		int waterHeight = 2048;

		std::shared_ptr<FrameBuffer> waterBuffer = FrameBuffer::Create(waterWidth, waterHeight, nullptr, false, false);
		waterBuffer->Name = "WaterBuffer";
		waterBuffer->SetParent(This.lock());

		waterBuffer->DrawTo();

		waterBuffer->SetAttachmentCount(1);

		waterBuffer->AttachTexture(0, Textures::Create(waterWidth, waterHeight, Enum::SampleType::Linear, Enum::WrapType::ClampExtend, Enum::DataType::Float, Enum::InternalFormat::RGB32F, Enum::Format::RGB), GL_COLOR_ATTACHMENT0, true);

		waterBuffer->BindAttachments();

		WaterBuffer = waterBuffer;

    // ADDED
    float Water_A[WATER_MAT_SIDE_LENGTH * WATER_MAT_SIDE_LENGTH];
    float Water_K[WATER_MAT_SIDE_LENGTH * WATER_MAT_SIDE_LENGTH];
    float Water_xRange;
    float Water_yRange;
    float Water_c;

    Water_xRange = 32;
    Water_yRange = 32;
    Water_c = 0.9f;



    for (int m = 1; m <= WATER_MAT_SIDE_LENGTH; ++m)
    {
      for (int n = 1; n <= WATER_MAT_SIDE_LENGTH; ++n)
      {
        Water_A[m - 1 + (n - 1) * WATER_MAT_SIDE_LENGTH] = HelperFunctions::CalculateAmn(m, n, Water_xRange, Water_yRange, waterWidth, waterHeight);
        Water_K[m - 1 + (n - 1) * WATER_MAT_SIDE_LENGTH] = HelperFunctions::CalculateKmn(m, n, Water_xRange, Water_yRange);
      }
    }

    Programs::WaterMatrix->Use();
    Programs::WaterMatrix->A.Set(Water_A, WATER_MAT_SIDE_LENGTH * WATER_MAT_SIDE_LENGTH);
    Programs::WaterMatrix->K.Set(Water_K, WATER_MAT_SIDE_LENGTH * WATER_MAT_SIDE_LENGTH);

    Programs::WaterMatrix->x_range.Set(Water_xRange);
    Programs::WaterMatrix->y_range.Set(Water_yRange);
    Programs::WaterMatrix->c.Set(Water_c);

    Programs::WaterMatrix->time.Set(Programs::WaterMatrix->mTime);

    Programs::WaterMatrix->resolution.Set(float(waterWidth), float(waterHeight));


		/***************************************************************************************************
		Water Buffer Config End
		***************************************************************************************************/

		std::shared_ptr<FrameBuffer> sceneBuffer = FrameBuffer::Create(width, height);
		sceneBuffer->Name = "SceneBuffer";
		sceneBuffer->SetParent(This.lock());

		SceneBuffer = sceneBuffer;

		std::shared_ptr<FrameBuffer> normalMapGenBuffer = FrameBuffer::Create(1, 1);
		normalMapGenBuffer->Name = "NormalMapGenBuffer";
		normalMapGenBuffer->SetParent(This.lock());

		NormalMapGenBuffer = normalMapGenBuffer;

		std::shared_ptr<FrameBuffer> lightingBuffer = FrameBuffer::Create(width, height);
		lightingBuffer->Name = "LightingBuffer";
		lightingBuffer->SetParent(This.lock());

		LightingBuffer = lightingBuffer;

		std::shared_ptr<FrameBuffer> accumulationBuffer = FrameBuffer::Create(width, height, nullptr, false, false);
		accumulationBuffer->Name = "AccumulationBuffer";
		accumulationBuffer->SetParent(This.lock());

		AccumulationBuffer = accumulationBuffer;

		std::shared_ptr<FrameBuffer> blurResult = FrameBuffer::Create(width, height, Textures::Create(width, height, Enum::SampleType::Linear, Enum::WrapType::ClampExtend), true, false);
		blurResult->Name = "BlurResult";
		blurResult->SetParent(This.lock());

		BlurResult = blurResult;

		std::shared_ptr<BlurOperation> blur = Engine::Create<BlurOperation>();
		blur->Output = BlurResult;
		blur->Detatch = false;
		blur->Configure(width, height, Enum::SampleType::Linear, Enum::WrapType::ClampExtend, Enum::DataType::Float, Enum::InternalFormat::RGBA16F, Enum::Format::RGBA);
		blur->SetParent(This.lock());

		Blur = blur;

		std::shared_ptr<HDRColorCorrectionOperation> colorCorrection = Engine::Create<HDRColorCorrectionOperation>();
		colorCorrection->Resize(width, height);
		colorCorrection->SetParent(This.lock());
		HDRColorCorrection = colorCorrection;

		sceneBuffer->DrawTo();
		sceneBuffer->SetAttachmentCount(7);

		sceneBuffer->AttachTexture(0, Textures::Create(width, height, Enum::SampleType::Linear, Enum::WrapType::ClampExtend, Enum::DataType::Float, Enum::InternalFormat::RGB32F, Enum::Format::RGB), GL_COLOR_ATTACHMENT0, true);
		sceneBuffer->AttachTexture(1, Textures::Create(width, height, Enum::SampleType::Linear, Enum::WrapType::ClampExtend, Enum::DataType::Float, Enum::InternalFormat::RGB32F, Enum::Format::RGB), GL_COLOR_ATTACHMENT1, true);
		sceneBuffer->AttachTexture(2, Textures::Create(width, height, Enum::SampleType::Linear, Enum::WrapType::ClampExtend, Enum::DataType::UnsignedByte, Enum::InternalFormat::RGBA, Enum::Format::RGBA), GL_COLOR_ATTACHMENT2, true);
		sceneBuffer->AttachTexture(3, Textures::Create(width, height, Enum::SampleType::Linear, Enum::WrapType::ClampExtend, Enum::DataType::UnsignedByte, Enum::InternalFormat::RGB8, Enum::Format::RGB), GL_COLOR_ATTACHMENT3, true);
		sceneBuffer->AttachTexture(4, Textures::Create(width, height, Enum::SampleType::Linear, Enum::WrapType::ClampExtend, Enum::DataType::UnsignedByte, Enum::InternalFormat::RGB8, Enum::Format::RGB), GL_COLOR_ATTACHMENT4, true);
		sceneBuffer->AttachTexture(5, Textures::Create(width, height, Enum::SampleType::Linear, Enum::WrapType::ClampExtend, Enum::DataType::UnsignedByte, Enum::InternalFormat::RGB8, Enum::Format::RGB), GL_COLOR_ATTACHMENT5, true);
		sceneBuffer->AttachTexture(6, Textures::Create(width, height, Enum::SampleType::Linear, Enum::WrapType::ClampExtend, Enum::DataType::Float, Enum::InternalFormat::RGBA16F, Enum::Format::RGBA), GL_COLOR_ATTACHMENT6, true);

		sceneBuffer->BindAttachments();

		accumulationBuffer->DrawTo();
		accumulationBuffer->SetAttachmentCount(1);

		accumulationBuffer->AttachTexture(0, Textures::Create(width, height, Enum::SampleType::Nearest, Enum::WrapType::ClampExtend, Enum::DataType::Float, Enum::InternalFormat::RGBA16F, Enum::Format::RGBA), GL_COLOR_ATTACHMENT0, true);

		accumulationBuffer->BindAttachments();

		lightingBuffer->DrawTo();
		lightingBuffer->SetAttachmentCount(2);

		lightingBuffer->AttachTexture(0, accumulationBuffer->GetTexture(), GL_COLOR_ATTACHMENT0, false);
		lightingBuffer->AttachTexture(1, sceneBuffer->GetTexture(6), GL_COLOR_ATTACHMENT1, false);

		lightingBuffer->BindAttachments();

		blur->SetInput(sceneBuffer->GetTexture(6));


		std::shared_ptr<FrameBuffer> hdrBuffer = FrameBuffer::Create(width, height, Textures::Create(width, height, Enum::SampleType::Nearest, Enum::WrapType::ClampExtend, Enum::DataType::Float, Enum::InternalFormat::RGBA16F, Enum::Format::RGBA), true, false);

		hdrBuffer->Name = "HDRBuffer";

		hdrBuffer->SetParent(This.lock());

		HDRBuffer = hdrBuffer;

		blur->Output = BlurResult;

		FrameBuffer::Detatch();

		std::shared_ptr<ShadingOperation> shader = Engine::Create<ShadingOperation>();

		shader->Resolution.Set(float(width), float(height));
		shader->SetParent(This.lock());

		Shader = shader;
	}

	std::shared_ptr<Texture> GlowingSceneOperation::GenerateNormalMap(const std::shared_ptr<Texture>& heightMap)
	{
		std::shared_ptr<Texture> normalMap = Textures::Create(heightMap->GetWidth(), heightMap->GetHeight(), Enum::SampleType::Linear, Enum::WrapType::Repeat, Enum::DataType::UnsignedByte, Enum::InternalFormat::RGBA, Enum::Format::RGBA);

		NormalMapQueue.push_back(TexturePair());

		NormalMapQueue.back().first = heightMap;
		NormalMapQueue.back().second = normalMap;

		return normalMap;
	}

	std::shared_ptr<class HDRColorCorrectionOperation> GlowingSceneOperation::GetHDRColorCorrection() const
	{
		return HDRColorCorrection.lock();
	}

	void GlowingSceneOperation::SetScene(const std::shared_ptr<Scene>& scene)
	{
		SceneDraw.lock()->CurrentScene = scene;
	}

	// [0] = Position
	// [1] = Normal
	// [2] = Diffuse
	// [3] = Specular
	// [4] = EmissiveAmbient
	// [5] = Scene

	void GlowingSceneOperation::Update(float dt)
	{
		RenderOperation::Update(dt);

		auto blur = Blur.lock();

		blur->Radius = Radius;
		blur->Sigma = Sigma;
		blur->Resolution = Resolution;
		blur->Transform = Transform;

		auto shader = Shader.lock();
		auto sceneDraw = SceneDraw.lock();
		auto currentScene = sceneDraw->CurrentScene.lock();

		shader->CurrentCamera = currentScene->CurrentCamera;
		shader->SceneBuffer = SceneBuffer;
		shader->LightBuffer = LightingBuffer;
		shader->CurrentScene = currentScene;
		shader->GlobalLight = currentScene->GlobalLight;
		shader->Update(0);

		Lights.CurrentCamera = currentScene->CurrentCamera;
		Lights.Clear();

		for (int i = 0; i < currentScene->GetLights(); ++i)
		{
			std::shared_ptr<Light> light = currentScene->GetLight(i);
		
			Lights.PushLight(light);
		}

		auto hdrColorCorrect = HDRColorCorrection.lock();

		hdrColorCorrect->Output = Output.lock();
		hdrColorCorrect->Input = HDRBuffer.lock()->GetTexture();

    // ADDED
    Programs::WaterMatrix->Use();
    Programs::WaterMatrix->mTime += dt;
    Programs::WaterMatrix->time.Set(Programs::WaterMatrix->mTime);
	}

	void GlowingSceneOperation::Render()
	{
		auto sceneDraw = SceneDraw.lock();
		auto currentScene = sceneDraw->CurrentScene.lock();

		if (sceneDraw->CurrentScene.expired() || currentScene->CurrentCamera.expired())
			return;

		glDisable(GL_BLEND); CheckGLErrors();
		glEnable(GL_DEPTH_TEST); CheckGLErrors();

		if (WaterEnabled)
		{
			WaterBuffer.lock()->DrawTo();

			Graphics::ClearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CheckGLErrors();

			Programs::WaterMatrix->Use();

			Programs::WaterMatrix->transform.Set(Matrix3());

			Programs::WaterMatrix->CoreMeshes.Square->Draw();
		}

		Programs::NormalMapGen->Use();

		Programs::NormalMapGen->transform.Set(Matrix3());

		for (int i = 0; i < int(NormalMapQueue.size()); ++i)
		{
			auto normalMapGenBuffer = NormalMapGenBuffer.lock();
			auto first = NormalMapQueue[i].first.lock();
			auto second = NormalMapQueue[i].second.lock();

			normalMapGenBuffer->Bind();
			normalMapGenBuffer->SetAttachmentCount(0);
			normalMapGenBuffer->Resize(Dimensions(first->GetWidth(), first->GetHeight()), true);

			normalMapGenBuffer->SetAttachmentCount(1);
			normalMapGenBuffer->Bind();
			normalMapGenBuffer->AttachTexture(0, second, GL_COLOR_ATTACHMENT0, false);
			normalMapGenBuffer->BindAttachments();

			normalMapGenBuffer->DrawTo(0, 0, first->GetWidth(), first->GetHeight());

			Graphics::ClearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CheckGLErrors();

			Programs::NormalMapGen->heightMap.Set(first, 1);
			Programs::NormalMapGen->scale.Set(2);
			Programs::NormalMapGen->resolution.Set(float(first->GetWidth()), float(first->GetHeight()));

			Programs::NormalMapGen->CoreMeshes.Square->Draw();
		}

		NormalMapQueue.clear();

		std::shared_ptr<Camera> camera = currentScene->CurrentCamera.lock();

		Programs::Phong->Use();

		Programs::Phong->useOffsetMap.Set(false);
		Programs::Phong->cameraTransform.Set(camera->GetTransformationInverse());
		Programs::Phong->transform.Set(camera->GetProjection());

		auto sceneBuffer = SceneBuffer.lock();

		sceneBuffer->DrawTo();
		Graphics::SetClearColor(RGBA(0, 0, 0, 1));
		Graphics::ClearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CheckGLErrors();

		currentScene->BuildRenderQueue(camera);

		currentScene->DrawTerrain(false);
		//currentScene->Draw(false);
		currentScene->DrawQueued(false);

		// ugly shit start

		Programs::DepthTrace->Use();

		AccumulationBuffer.lock()->DrawTo();

		Graphics::ClearScreen(GL_COLOR_BUFFER_BIT); CheckGLErrors();

		auto lightingBuffer = LightingBuffer.lock();

		glBindFramebuffer(GL_READ_FRAMEBUFFER, sceneBuffer->GetID()); CheckGLErrors();
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, lightingBuffer->GetID()); CheckGLErrors();

		glBlitFramebuffer(
			0, 0, sceneBuffer->GetWidth(), sceneBuffer->GetHeight(),
			0, 0, sceneBuffer->GetWidth(), sceneBuffer->GetHeight(),
			GL_DEPTH_BUFFER_BIT,
			GL_NEAREST
		); CheckGLErrors();

		lightingBuffer->DrawTo();

		Shader.lock()->Render();

		glEnable(GL_DEPTH_TEST); CheckGLErrors();

		if (DrawSkyBox && !SkyBox.expired())
		{
			std::shared_ptr<CubeMapTexture> skyBox = SkyBox.lock();

			Vector3 camDim = camera->GetDimensions();
			float projectionPlane = camera->GetProjectionPlane();
			Matrix3 transform = camera->GetTransformation();

			Programs::SkyBox->Use();

			Programs::SkyBox->cameraRight.Set(0.5f * camDim.X * transform.RightVector());
			Programs::SkyBox->cameraUp.Set(0.5f * camDim.Y * transform.UpVector());
			Programs::SkyBox->cameraFront.Set(-projectionPlane * transform.FrontVector());

			Programs::SkyBox->skyBrightness.Set(SkyBrightness);
			Programs::SkyBox->skyBackgroundBrightness.Set(SkyBackgroundBrightness);
			Programs::SkyBox->skyColor.Set(SkyColor);
			Programs::SkyBox->skyBackgroundColor.Set(SkyBackgroundColor);

			Programs::SkyBox->skyLeft.Set(skyBox->Left.lock());
			Programs::SkyBox->skyRight.Set(skyBox->Right.lock(), 1);
			Programs::SkyBox->skyTop.Set(skyBox->Top.lock(), 2);
			Programs::SkyBox->skyBottom.Set(skyBox->Bottom.lock(), 3);
			Programs::SkyBox->skyFront.Set(skyBox->Front.lock(), 4);
			Programs::SkyBox->skyBack.Set(skyBox->Back.lock(), 5);

			Programs::SkyBox->CoreMeshes.Square->Draw();
		}

		Programs::Phong->Use();

		Programs::Phong->useOffsetMap.Set(false);
		Programs::Phong->offsetAmplitude.Set(1);
		Programs::Phong->offsetMinCoord.Set(Vector3(-272, -256));
		Programs::Phong->offsetMaxCoord.Set(Vector3(316, 300));
		Programs::Phong->offsetMap.Set(WaterBuffer.lock()->GetTexture());

		Programs::PhongForward->Use();

		Programs::PhongForward->useOffsetMap.Set(false);
		Programs::PhongForward->offsetAmplitude.Set(1);
		Programs::PhongForward->offsetMinCoord.Set(Vector3(-272, -256));
		Programs::PhongForward->offsetMaxCoord.Set(Vector3(316, 300));
		Programs::PhongForward->offsetMap.Set(WaterBuffer.lock()->GetTexture());
		Programs::PhongForward->cameraTransform.Set(camera->GetTransformationInverse());
		Programs::PhongForward->transform.Set(camera->GetProjection());

		glEnable(GL_BLEND); CheckGLErrors();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); CheckGLErrors();

		Lights.Flush();

		if (currentScene->GlobalLight.expired())
		{
			Programs::PhongForward->globalBrightness.Set(1);
			Programs::PhongForward->globalLightDirection.Set(-currentScene->CurrentCamera.lock()->GetTransformationInverse().UpVector());
			Programs::PhongForward->globalDiffuse.Set(1, 1, 1);
			Programs::PhongForward->globalSpecular.Set(1, 1, 1);
			Programs::PhongForward->globalAmbient.Set(1, 1, 1);
		}
		else
		{
			auto globalLight = currentScene->GlobalLight.lock();

			Programs::PhongForward->globalBrightness.Set(globalLight->Brightness);
			Programs::PhongForward->globalLightDirection.Set(currentScene->CurrentCamera.lock()->GetTransformationInverse() * -globalLight->Direction);
			Programs::PhongForward->globalDiffuse.Set(globalLight->Diffuse);
			Programs::PhongForward->globalSpecular.Set(globalLight->Specular);
			Programs::PhongForward->globalAmbient.Set(globalLight->Ambient);
		}

		//currentScene->Draw(true);
		currentScene->DrawQueued(true);

		Blur.lock()->Render();

		glDisable(GL_DEPTH_TEST);  CheckGLErrors();

		auto hdrBuffer = HDRBuffer.lock();

		hdrBuffer->DrawTo();

		Programs::BlurBlend->Use();
		Programs::BlurBlend->resolution.Set(Resolution);
		Programs::BlurBlend->textureData.Set(LightingBuffer.lock()->GetTexture());
		Programs::BlurBlend->blurData.Set(BlurResult.lock()->GetTexture(), 1);
		Programs::BlurBlend->transform.Set(Matrix3());

		Graphics::ClearScreen(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CheckGLErrors();

		Programs::BlurBlend->CoreMeshes.Square->Draw();

		glEnable(GL_DEPTH_TEST); CheckGLErrors();

		GetHDRColorCorrection()->Render();

		if (!Output.expired() && Detatch)
			FrameBuffer::Detatch();

		glEnable(GL_DEPTH_TEST); CheckGLErrors();
	}

	std::shared_ptr<FrameBuffer> GlowingSceneOperation::GetSceneBuffer() const
	{
		return SceneBuffer.lock();
	}

	std::shared_ptr<FrameBuffer> GlowingSceneOperation::GetLightingBuffer() const
	{
		return LightingBuffer.lock();
	}

	std::shared_ptr<FrameBuffer> GlowingSceneOperation::GetHorizontalPass() const
	{
		return Blur.lock()->GetHorizontalPass();
	}

	std::shared_ptr<FrameBuffer> GlowingSceneOperation::GetVerticalPass() const
	{
		return Blur.lock()->Output.lock();
	}
}
