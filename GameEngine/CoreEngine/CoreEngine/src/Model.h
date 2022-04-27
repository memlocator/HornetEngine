#pragma once

#include "Mesh.h"
#include "RGBA.h"
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
		void Update(float);

		float Reflectivity = 0;
		RGBA Color;
		RGBA GlowColor = RGBA(0, 0, 0, 1);
		std::weak_ptr<Engine::ModelAsset> Asset;

		void Draw(const std::shared_ptr<Camera>& camera);
		std::string GetMeshName() const;
		bool IsTransparent() const;
		Aabb GetBoundingBox() const;
		Aabb GetLocalBoundingBox() const;
		Matrix3 GetTransformation() const;
		Matrix3 GetInverseTransformation() const;
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