#pragma once

#include "Vector3.h"

class Aabb;

class Ray
{
public:
	Vector3 Start;
	Vector3 Direction;

	constexpr Ray() {}
	constexpr Ray(const Vector3& start, const Vector3& direction) : Start(start), Direction(direction) {}

	bool Intersects(const Aabb& box, Float& t, Float epsilon = 1e-5f) const;

private:
	bool IntersectsAxis(Float start, Float direction, Float min, Float max, Float& tMin, Float& tMax, Float epsilon = 1e-5f) const;
};

