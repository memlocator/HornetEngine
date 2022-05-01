#pragma once

#include "Mesh.h"
#include "Color4.h"
#include "Scene.h"

namespace Engine
{
	class Transform;
	class ModelAsset;
}

namespace GraphicsEngine
{
	class Texture;
	class Camera;

	class Model : public SceneObject
	{
	public:
		virtual ~Model() {}

		void Initialize();
		void Update(Float);

		float Reflectivity = 0;
		Color4 Color;
		Color4 GlowColor = Color4(0.f, 0.f, 0.f, 1.f);
		std::weak_ptr<Engine::ModelAsset> Asset;

		void Draw(const std::shared_ptr<Camera>& camera);
		std::string GetMeshName() const;
		bool IsTransparent() const;
		Aabb GetBoundingBox() const;
		Aabb GetLocalBoundingBox() const;
		Matrix4 GetTransformation() const;
		Matrix4 GetInverseTransformation() const;
		bool HasMoved() const;
		bool IsStatic() const;
		void CastRay(const Ray& ray, const CastResultsCallback& callback) const;
		int GetMeshId() const;

	private:
		void DrawMesh(const std::shared_ptr<Camera>& camera, const Mesh* mesh) const;
		void DrawForward(const std::shared_ptr<Camera>& camera, const Mesh* mesh) const;
		void DrawShadow(const std::shared_ptr<Camera>& camera, const Mesh* mesh) const;
		void DrawDepth(const std::shared_ptr<Camera>& camera, const Mesh* mesh) const;

		Engine::Transform* TransformObject = nullptr;
		Engine::ModelAsset* AssetObject = nullptr;
	};
}