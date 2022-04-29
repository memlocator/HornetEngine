#include "Aabb.h"

#include <algorithm>

#include "MeshLoader.h"


Aabb& Aabb::Expand(const Vector3& point)
{
	Min.X = cmath::min(Min.X, point.X);
	Min.Y = cmath::min(Min.Y, point.Y);
	Min.Z = cmath::min(Min.Z, point.Z);
	Max.X = cmath::max(Max.X, point.X);
	Max.Y = cmath::max(Max.Y, point.Y);
	Max.Z = cmath::max(Max.Z, point.Z);

	return *this;
}

bool Aabb::ContainsPoint(const Vector3& point) const
{
	return (
		InRange(point.X, Min.X, Max.X) &&
		InRange(point.Y, Min.Y, Max.Y) &&
		InRange(point.Z, Min.Z, Max.Z)
		);
}

bool Aabb::Intersects(const Aabb& box) const
{
	return Aabb(Min, Max + box.GetSize()).ContainsPoint(box.Max);
}

bool Aabb::InRange(Float x, Float min, Float max) const
{
	return x >= min && x <= max;
}

Vector3 Aabb::GetCenter() const
{
	return 0.5 * (Min + Max);
}

Vector3 Aabb::GetSize() const
{
	return Max - Min;
}

typename Enum::IntersectionType Aabb::Intersects(const Plane& plane, Float epsilon) const
{
	Vector3 center = 0.5_F * (Min + Max);
	Vector3 halfExtent = Max - center;

	Vector3 normal = plane;
	Vector3 absNormal;

	absNormal.X = cmath::abs(normal.X);
	absNormal.Y = cmath::abs(normal.Y);
	absNormal.Z = cmath::abs(normal.Z);

	normal.W = 0;

	Float projectionRadius = halfExtent * absNormal;
	Float centerProjectionRadius = normal * center - plane.W;

	if (cmath::abs(centerProjectionRadius) <= projectionRadius)
		return Enum::IntersectionType::Overlaps;
	else if (centerProjectionRadius > 0)
		return Enum::IntersectionType::Inside;
	else
		return Enum::IntersectionType::Outside;

}

void Aabb::Compute(const std::vector<Vector3>& points)
{
	Min.Set(FLT_MAX, FLT_MAX, FLT_MAX);
	Max.Set(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	for (size_t i = 0; i < points.size(); ++i)
	{
		const Vector3& point = points[i];
		Min = MinVector(Min, point);
		Max = MaxVector(Max, point);
	}
}

Aabb Aabb::Transform(const Matrix4& transformation) const
{
	Vector3 translation = transformation.Translation();

	Float min[3] = { Min.X, Min.Y, Min.Z };
	Float max[3] = { Max.X, Max.Y, Max.Z };

	Float outMin[3] = { translation.X, translation.Y, translation.Z };
	Float outMax[3] = { translation.X, translation.Y, translation.Z };

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			Float a = transformation.Data[i][j] * min[j];
			Float b = transformation.Data[i][j] * max[j];

			if (a > b)
				std::swap(a, b);

			outMin[i] += a;
			outMax[i] += b;
		}
	}

	return Aabb(
		Vector3(outMin[0], outMin[1], outMin[2], 1._F),
		Vector3(outMax[0], outMax[1], outMax[2], 1._F)
	);
}

Aabb Aabb::GetSubRegion(int region) const
{
	return Aabb();
}

bool Aabb::operator==(const Aabb& other) const
{
	return Min == other.Min && Max == other.Max;
}

bool Aabb::operator!=(const Aabb& other) const
{
	return Min != other.Min || Max != other.Max;
}