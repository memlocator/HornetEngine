#include "DebugDraw.h"

#include "Model.h"
#include "Transform.h"

void DebugDraw::Initialize()
{
	Engine::Object::Initialize();

	auto debugScene = Engine::Create<GraphicsEngine::Scene>();

	debugScene->SetParent(This.lock());

	DebugScene = debugScene;
}

std::shared_ptr<GraphicsEngine::Scene> DebugDraw::GetScene()
{
	return DebugScene.lock();
}

void DebugDraw::Reset()
{
	for (int i = 0; i < int(DebugObjects.size()); ++i)
	{
		DebugScene.lock()->RemoveObject(DebugObjects[i].lock()->Get<GraphicsEngine::Model>());

		AvailableDebugObjects.push_back(std::weak_ptr<Engine::Transform>());
		AvailableDebugObjects.back() = DebugObjects[i];
	}

	DebugObjects.clear();
}

void DebugDraw::Clear()
{
	Reset();

	AvailableDebugObjects.clear();
}

void DebugDraw::DrawLine(const Vector3& point1, const Vector3& point2, const Color4& color, Float thickness, bool glows)
{

	Vector3 vector = point2 - point1;
	Float length = vector.Length();

	vector.Normalize();

	Vector3 up = Vector3(0, 1, 0);

	if (vector.X >= -1e-5f && vector.X <= 1e-5f && vector.Z >= -1e-5f && vector.Z <= 1e-5f)
		up = Vector3(1, 0, 0);

	PlaceObject(
		Matrix4(true).Translate(0.5f * length * vector) * Matrix4(point1, vector, up) * Matrix4(true).Scale(thickness, thickness, 0.5f * length),
		color,
		thickness,
		glows,
		LineAsset.lock()
	);
}

void DebugDraw::DrawTriangle(const Vector3& point1, const Vector3& point2, const Vector3& point3, const Color4& color, Float thickness, bool glows)
{
	Vector3 ab = point2 - point1;
	Vector3 ac = point3 - point1;

	Vector3 normal = ac.Cross(ab).Normalize();
	
	Float squareDistance = ac.Dot(ac);
	Float distance = std::sqrt(squareDistance);
	Float dot = ab.Dot(ac) / squareDistance;
	Float distance1 = dot * distance;
	
	Float v2x = ac.X / distance;
	Float v2y = ac.Y / distance;
	Float v2z = ac.Z / distance;
	
	Float v1x = v2y * normal.Z - v2z * normal.Y;
	Float v1y = v2z * normal.X - v2x * normal.Z;
	Float v1z = v2x * normal.Y - v2y * normal.X;
	
	Float dx = ab.X - dot * ac.X;
	Float dy = ab.Y - dot * ac.Y;
	Float dz = ab.Z - dot * ac.Z;
	
	Float height = -(v1x * dx + v1y * dy + v1z * dz);
	
	PlaceObject(
		(
			Matrix4(
				Vector3(0.5f * (point1.X + point2.X) + 0.1f * normal.X, 0.5f * (point1.Y + point2.Y) + 0.1f * normal.Y, 0.5f * (point1.Z + point2.Z) + 0.1f * normal.Z),
				Vector3(normal.X, -v2x, v1x),
				Vector3(normal.Y, -v2y, v1y),
				Vector3(normal.Z, -v2z, v1z)
			) *
			Matrix4(true).Scale(thickness, 0.5f * distance1, 0.5f * height)
		),
		color,
		thickness,
		glows,
		LineAsset.lock()
	);

	PlaceObject(
		(
			Matrix4(
				Vector3(0.5f * (point2.X + point3.X) + 0.1f * normal.X, 0.5f * (point2.Y + point3.Y) + 0.1f * normal.Y, 0.5f * (point3.Z + point3.Z) + 0.1f * normal.Z),
				Vector3(normal.X, -v1x, -v2x),
				Vector3(normal.Y, -v1y, -v2y),
				Vector3(normal.Z, -v1z, -v2z)
			) *
			Matrix4(true).Scale(thickness, 0.5f * height, 0.5f * (distance - distance1))
			),
		color,
		thickness,
		glows,
		LineAsset.lock()
	);
}

std::shared_ptr<Engine::Transform> DebugDraw::NewObject(const Matrix4& transformation)
{
	std::shared_ptr<Engine::Transform> object;

	if (AvailableDebugObjects.size() > 0)
	{
		object = AvailableDebugObjects.back().lock();

		AvailableDebugObjects.pop_back();
	}
	else
	{
		object = Engine::Create<Engine::Transform>();

		object->SetStatic(false);

		Engine::Create<GraphicsEngine::Model>()->SetParent(object);
	}

	DebugObjects.push_back(std::weak_ptr<Engine::Transform>());
	DebugObjects.back() = object;

	object->SetParent(This.lock());

	object->SetTransformation(transformation);

	DebugScene.lock()->AddObject(object->Get<GraphicsEngine::Model>());

	return object;
}

void DebugDraw::PlaceObject(const Matrix4& transformation, const Color4& color, Float thickness, bool glows, const std::shared_ptr<Engine::ModelAsset>& asset)
{
	std::shared_ptr<Engine::Transform> transform = NewObject(transformation);
	std::shared_ptr<GraphicsEngine::Model> model = transform->Get<GraphicsEngine::Model>();

	model->Color = color;

	if (glows)
		model->GlowColor = color;
	else
		model->GlowColor = 0x00000000;

	model->Asset = asset;
	model->SetMaterial(MaterialProperties.lock());
}