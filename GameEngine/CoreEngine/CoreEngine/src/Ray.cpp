#include "Ray.h"

#include <limits>

bool Ray::Intersects(const Aabb& box, float& t, float epsilon) const
{
	float tMax = std::numeric_limits<float>::max();;
	float tMin = -tMax;

	if (!(
		IntersectsAxis(Start.X, Direction.X, box.Min.X, box.Max.X, tMin, tMax, epsilon) &&
		IntersectsAxis(Start.Y, Direction.Y, box.Min.Y, box.Max.Y, tMin, tMax, epsilon) &&
		IntersectsAxis(Start.Z, Direction.Z, box.Min.Z, box.Max.Z, tMin, tMax, epsilon)
		) || tMax < 0)
		return false;

	t = std::max(0.f, tMin);

	return true;
}

bool Ray::IntersectsAxis(float start, float direction, float min, float max, float& tMin, float& tMax, float epsilon) const
{
	if (direction < -epsilon || direction > epsilon)
	{
		float t1 = (min - start) / direction;
		float t2 = (max - start) / direction;

		if (t1 > t2)
		{
			tMin = std::max(tMin, t2);
			tMax = std::min(tMax, t1);
		}
		else
		{
			tMin = std::max(tMin, t1);
			tMax = std::min(tMax, t2);
		}
	}
	else
		return start >= min && start <= max;

	return tMin <= tMax;
}