#include "GlowingSceneOperation.h"

#include "CubeMap.h"
#include "FrameBuffer.h"
#include "Light.h"
#include "HDRColorCorrectionOperation.h"
#include "Texture.h"
#include "Scene.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<GlowingSceneOperation>()
		{
			Reflect<GlowingSceneOperation, RenderOperation>::Class
			(
				"GlowingSceneOperation",
				{ "GameObject" },

				Member<Bind(&GlowingSceneOperation::WaterEnabled)>("WaterEnabled"),
				Member<Bind(&GlowingSceneOperation::Detatch)>("Detatch"),
				Member<Bind(&GlowingSceneOperation::DrawSkyBox)>("DrawSkyBox"),
				Member<Bind(&GlowingSceneOperation::SkyBox)>("SkyBox"),
				Member<Bind(&GlowingSceneOperation::SkyBrightness)>("SkyBrightness"),
				Member<Bind(&GlowingSceneOperation::SkyBackgroundBrightness)>("SkyBackgroundBrightness"),
				Member<Bind(&GlowingSceneOperation::SkyColor)>("SkyColor"),
				Member<Bind(&GlowingSceneOperation::SkyBackgroundColor)>("SkyBackgroundColor"),
				Member<Bind(&GlowingSceneOperation::Radius)>("Radius"),
				Member<Bind(&GlowingSceneOperation::Sigma)>("Sigma"),
				Member<Bind(&GlowingSceneOperation::Resolution)>("Resolution"),
				Member<Bind(&GlowingSceneOperation::Transform)>("Transform"),
				Member<Bind(&GlowingSceneOperation::Output)>("Output"),
				Member<Bind(&GlowingSceneOperation::DebugViewLight)>("DebugViewLight"),

				Function(
					"Configure",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<int>("width"),
						Argument<int>("height"),
						Argument<const std::shared_ptr<Scene>&>("scene"),
						Argument<const std::shared_ptr<FrameBuffer>&>("output")
					).Bind<GlowingSceneOperation, &GlowingSceneOperation::Configure>()
				),

				Function(
					"SetScene",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Scene>&>("scene")
					).Bind<GlowingSceneOperation, &GlowingSceneOperation::SetScene>()
				),

				Function(
					"GetSceneBuffer",
					Overload(
						Const,
						Returns<std::shared_ptr<FrameBuffer>>()
					).Bind<GlowingSceneOperation, &GlowingSceneOperation::GetSceneBuffer>()
				),

				//Function(
				//	"GetLuminescenceBuffer",
				//	Overload(
				//		Const,
				//		Returns<std::shared_ptr<FrameBuffer>>()
				//	).Bind<GlowingSceneOperation, &GlowingSceneOperation::GetLuminescenceBuffer>()
				//),

				Function(
					"GetLightingBuffer",
					Overload(
						Const,
						Returns<std::shared_ptr<FrameBuffer>>()
					).Bind<GlowingSceneOperation, &GlowingSceneOperation::GetLightingBuffer>()
				),

				Function(
					"GetHorizontalPass",
					Overload(
						Const,
						Returns<std::shared_ptr<FrameBuffer>>()
					).Bind<GlowingSceneOperation, &GlowingSceneOperation::GetHorizontalPass>()
				),

				Function(
					"GetVerticalPass",
					Overload(
						Const,
						Returns<std::shared_ptr<FrameBuffer>>()
					).Bind<GlowingSceneOperation, &GlowingSceneOperation::GetVerticalPass>()
				),

				Function(
					"GenerateNormalMap",
					Overload(
						Mutable,
						Returns<std::shared_ptr<Texture>>(),
						Argument<const std::shared_ptr<Texture>&>("heightMap")
					).Bind<GlowingSceneOperation, &GlowingSceneOperation::GenerateNormalMap>()
				),

				Function(
					"GetHDRColorCorrection",
					Overload(
						Const,
						Returns<std::shared_ptr<HDRColorCorrectionOperation>>()
					).Bind<GlowingSceneOperation, &GlowingSceneOperation::GetHDRColorCorrection>()
				)
			);
		}
	}
}