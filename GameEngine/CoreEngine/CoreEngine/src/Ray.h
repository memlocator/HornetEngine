#pragma once

#include <limits>

#include "Vector3.h"
#include "Aabb.h"

class Ray
{
public:
	Vector3 Start;
	Vector3 Direction;

	constexpr Ray() {}
	constexpr Ray(const Vector3& start, const Vector3& direction) : Start(start), Direction(direction) {}

	bool Intersects(const Aabb& box, float& t, float epsilon = 1e-5f) const;

private:
	bool IntersectsAxis(float start, float direction, float min, float max, float& tMin, float& tMax, float epsilon = 1e-5f) const;
};

