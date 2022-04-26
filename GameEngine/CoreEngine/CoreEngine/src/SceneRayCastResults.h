#pragma once

#include <memory>
#include <functional>

#include "Vector3.h"

namespace Engine
{
	class Object;
}

namespace GraphicsEngine
{
	class Material;
}

struct SceneRayCastResults
{
	float Distance = -1;
	float Reflectivity = 0;
	Vector3 Intersection;
	Vector3 Normal;
	Vector3 Color;
	Vector3 GlowColor;
	std::shared_ptr<GraphicsEngine::Material> MaterialProperties;
	std::shared_ptr<Engine::Object> Hit;

	bool operator<(const SceneRayCastResults& other) const
	{
		if (Distance == -1)
			return true;

		return Distance < other.Distance;
	}

	operator std::string() const;
};

typedef std::function<void(const SceneRayCastResults& results)> CastResultsCallback;