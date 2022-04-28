#pragma once

#include <vector>

#include "Vector3.h"
#include "Matrix3.h"
#include "Plane.h"
#include "ConstMath.h"

class Aabb
{
public:
	struct AxisEnum
	{
		enum Axis
		{
			MinX = 0,
			MinY = 0,
			MinZ = 0,

			MaxX = 1,
			MaxY = 2,
			MaxZ = 4
		};
	};

	typedef AxisEnum::Axis Axis;

	Vector3 Min;
	Vector3 Max;

	constexpr Aabb(const Vector3& min = Vector3(0, 0, 0, 1), const Vector3& max = Vector3(0, 0, 0, 1)) : Min(min), Max(max)
	{
		Min.W = 1;
		Max.W = 1;
	}

	Aabb& Expand(const Vector3& point);
	bool ContainsPoint(const Vector3& point) const;
	bool Intersects(const Aabb& box) const;
	bool InRange(Float x, Float min, Float max) const;
	Vector3 GetCenter() const;
	Vector3 GetSize() const;
	Aabb Transform(const Matrix3& transformation) const;
	Aabb GetSubRegion(int region) const;

	Enum::IntersectionType Intersects(const Plane& plane, Float epsilon = 1e-5f) const;

	void Compute(const std::vector<Vector3>& points);

	bool operator==(const Aabb& other) const;
	bool operator!=(const Aabb& other) const;
};

namespace Enum
{
	typedef Aabb::Axis Axis;
}

// Helper functions
namespace {
	constexpr Vector3 MinVector(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 minVector;

		for (unsigned i = 0; i < 3; ++i)
		{
			minVector[i] = (lhs[i] < rhs[i]) ? lhs[i] : rhs[i];
		}

		return minVector;
	}

	constexpr Vector3 MaxVector(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 maxVector;

		for (unsigned i = 0; i < 3; ++i)
		{
			maxVector[i] = (lhs[i] > rhs[i]) ? lhs[i] : rhs[i];
		}

		return maxVector;
	}
}
