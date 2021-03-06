#include "Model.h"

#include "Constants.h"
#include "Graphics.h"
#include "Transform.h"
#include "Camera.h"
#include "Texture.h"
#include "ModelAsset.h"
#include "ShaderPrograms.h"

namespace GraphicsEngine
{
	void Model::Initialize()
	{
		SceneObject::Initialize();

		SetTicks(false);
	}

	void Model::Update(Float delta)
	{
		SceneObject::Update(delta);
		//if (Color.A <= 0.001f)
		//	Visible = false;
		//
		//if (TransformObject == nullptr)
		//	TransformObject = GetComponent<Engine::Transform>().get();
		//
		//if (AssetObject == nullptr)
		//	AssetObject = Asset.lock().get();
	}

	void Model::Draw(const std::shared_ptr<Camera>& camera)
	{
		if (TransformObject == nullptr)
			TransformObject = GetComponent<Engine::Transform>().get();

		if (AssetObject == nullptr)
			AssetObject = Asset.lock().get();
		
		if (TransformObject == nullptr)
			TransformObject = GetComponent<Engine::Transform>().get();

		//std::shared_ptr<Engine::Transform> transform = GetComponent<Engine::Transform>();

		if (TransformObject == nullptr || AssetObject == nullptr)
			return;

		const ShaderProgram* program = ShaderProgram::GetCurrentProgram();

		const Mesh* mesh = ShaderProgram::GetCurrentProgram()->Meshes->GetMesh(AssetObject->GetMeshID());

		if (mesh != nullptr)
		{
			if (program == Programs::Phong)
				DrawMesh(camera, mesh);
			else if (program == Programs::PhongForward)
				DrawForward(camera, mesh);
			else if (program == Programs::ShadowMap)
				DrawShadow(camera, mesh);
			else if (program == Programs::DepthTrace)
				DrawDepth(camera, mesh);
		}
	}

	void Model::DrawMesh(const std::shared_ptr<Camera>& camera, const Mesh* mesh) const
	{
		Programs::Phong->objectTransform.Set(TransformObject->GetWorldTransformation());

		Programs::Phong->color.Set(Color);

		mesh->Draw();
	}

	void Model::DrawForward(const std::shared_ptr<Camera>& camera, const Mesh* mesh) const
	{
		Programs::PhongForward->objectTransform.Set(TransformObject->GetWorldTransformation());

		Programs::PhongForward->color.Set(Color);

		mesh->Draw();
	}

	void Model::DrawShadow(const std::shared_ptr<Camera>& camera, const Mesh* mesh) const
	{
		Matrix4 transform = camera->GetTransformationInverse() * TransformObject->GetWorldTransformation();
		Programs::ShadowMap->transform.Set(camera->GetProjectionMatrix() * transform);
		Programs::ShadowMap->objectZTransform.Set(transform.Data[2][0], transform.Data[2][1], transform.Data[2][2], transform.Data[2][3]);

		mesh->Draw();
	}

	void Model::DrawDepth(const std::shared_ptr<Camera>& camera, const Mesh* mesh) const
	{
		Matrix4 transform = camera->GetTransformationInverse() * TransformObject->GetWorldTransformation();

		Programs::DepthTrace->transform.Set(camera->GetProjectionMatrix() * transform);
		Programs::DepthTrace->objectTransform.Set(transform);

		mesh->Draw();
	}

	std::string Model::GetMeshName() const
	{
		Engine::ModelAsset* asset = AssetObject;

		if (asset == nullptr)
			asset = Asset.lock().get();

		if (asset == nullptr)
			return "";

		return asset->Name;
	}

	bool Model::IsTransparent() const
	{
		return Color.A != 1;
	}

	Aabb Model::GetBoundingBox() const
	{
		Engine::ModelAsset* asset = AssetObject;

		if (asset == nullptr)
			asset = Asset.lock().get();

		if (asset == nullptr)
			return Aabb();

		const MeshData* data = MeshLoader::GetMeshData(asset->GetMeshID());

		//std::shared_ptr<Engine::Transform> transform = GetComponent<Engine::Transform>();
		Engine::Transform* transform = TransformObject;

		if (transform == nullptr)
			transform = GetComponent<Engine::Transform>().get();

		if (transform == nullptr)
			return Aabb();
		
		if (data == nullptr)
			return Aabb().Transform(transform->GetWorldTransformation());

		return Aabb(data->GetMinimumCorner(), data->GetMaximumCorner()).Transform(transform->GetWorldTransformation());
	}

	Aabb Model::GetLocalBoundingBox() const
	{
		Engine::ModelAsset* asset = AssetObject;

		if (asset == nullptr)
			asset = Asset.lock().get();

		if (asset == nullptr)
			return Aabb();

		const MeshData* data = MeshLoader::GetMeshData(asset->GetMeshID());

		//std::shared_ptr<Engine::Transform> transform = GetComponent<Engine::Transform>();

		return Aabb(data->GetMinimumCorner(), data->GetMaximumCorner());
	}

	Matrix4 Model::GetTransformation() const
	{
		Engine::Transform* transform = TransformObject;

		if (transform == nullptr)
			transform = GetComponent<Engine::Transform>().get();

		if (transform == nullptr)
			return Matrix4();

		return transform->GetWorldTransformation();
	}

	Matrix4 Model::GetInverseTransformation() const
	{
		Engine::Transform* transform = TransformObject;

		if (transform == nullptr)
			transform = GetComponent<Engine::Transform>().get();

		if (transform == nullptr)
			return Matrix4();

		return transform->GetWorldTransformationInverse();
	}

	bool Model::HasMoved() const
	{
		//std::shared_ptr<Engine::Transform> transform = GetComponent<Engine::Transform>();
		Engine::Transform* transform = TransformObject;

		if (transform == nullptr)
			transform = GetComponent<Engine::Transform>().get();

		if (transform != nullptr)
			return transform->HasMoved();

		return false;
	}

	bool Model::IsStatic() const
	{
		//std::shared_ptr<Engine::Transform> transform = GetComponent<Engine::Transform>();
		Engine::Transform* transform = TransformObject;

		if (transform == nullptr)
			transform = GetComponent<Engine::Transform>().get();

		if (transform != nullptr)
			return transform->IsTransformStatic();

		return true;
	}

	void Model::CastRay(const Ray& ray, const CastResultsCallback& callback) const
	{
		//std::shared_ptr<Engine::Transform> transform = GetComponent<Engine::Transform>();
		Engine::Transform* transform = TransformObject;

		if (transform == nullptr)
			transform = GetComponent<Engine::Transform>().get();

		Engine::ModelAsset* asset = AssetObject;

		if (asset == nullptr)
			asset = Asset.lock().get();

		if (transform == nullptr || asset == nullptr)
			return;

		int meshID = asset->GetMeshID();

		const MeshData* data = MeshLoader::GetMeshData(meshID);
		const Matrix4& transformation = transform->GetWorldTransformationInverse();

		auto resultsProcessorLambda = [this, &callback, &transform] (const SceneRayCastResults& results)
		{
			callback(SceneRayCastResults{
				results.Distance,
				Reflectivity,
				transform->GetWorldTransformation() * results.Intersection,
				transform->GetWorldNormalTransformation() * results.Normal,
				Color,
				(Float)GlowColor.A * Vector3(GlowColor).Scale(Vector3(1, 1, 1)),
				GetMaterial(),
				This.lock()
			});
		};

		data->CastRay(Ray(transformation * ray.Start, transformation * ray.Direction), std::ref(resultsProcessorLambda));
	}

	int Model::GetMeshId() const
	{
		Engine::ModelAsset* asset = AssetObject;

		if (asset == nullptr)
			asset = Asset.lock().get();

		if (asset == nullptr)
			return -1;

		return asset->GetMeshID();
	}
}
