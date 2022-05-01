#pragma once

import <memory>;

#include "Object.h"
#include "Vector3.h"
#include "Color4.h"
#include "Matrix4.h"

namespace Engine
{
	class Transform;
	class ModelAsset;
}

namespace GraphicsEngine
{
	class Model;
	class Material;
	class ModelAsset;
	class Scene;
}

class DebugDraw : public Engine::Object
{
public:
	void Initialize();

	void Update(Float) {}

	std::weak_ptr<Engine::ModelAsset> LineAsset;
	std::weak_ptr<Engine::ModelAsset> TriangleAsset;
	std::weak_ptr<GraphicsEngine::Material> MaterialProperties;

	std::shared_ptr<GraphicsEngine::Scene> GetScene();
	void Reset();
	void Clear();
	void DrawLine(const Vector3& point1, const Vector3& point2, const Color4& color = 0xFFFFFFFF, Float thickness = 0.1f, bool glows = false);
	void DrawTriangle(const Vector3& point1, const Vector3& point2, const Vector3& point3, const Color4& color = 0xFFFFFFFF, Float thickness = 0.1f, bool glows = false);

private:
	typedef std::vector<std::weak_ptr<Engine::Transform>> ObjectVector;

	std::weak_ptr<GraphicsEngine::Scene> DebugScene;

	ObjectVector AvailableDebugObjects;
	ObjectVector DebugObjects;
	
	std::shared_ptr<Engine::Transform> NewObject(const Matrix4& transformation);
	void PlaceObject(const Matrix4& transformation, const Color4& color, Float thickness, bool glows, const std::shared_ptr<Engine::ModelAsset>& asset);
};
