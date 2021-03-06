#include "Plane.h"

void Plane::Set(const Vector3& position, const Vector3& normal)
{
	Vector3 normalized = normal.Unit();
	Vector3::Set(normalized.X, normalized.Y, normalized.Z, position * normalized);
}

typename Enum::IntersectionType Plane::Compare(const Vector3& point, Float epsilon) const
{
	Float projection = Dot(Vector3(point.X, point.Y, point.Z, -1._F));

	if (projection > epsilon)
		return IntersectionType::Inside;
	else if (projection < -epsilon)
		return IntersectionType::Outside;
	else
		return IntersectionType::Coplanar;
}