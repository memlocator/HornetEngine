#include "Ray.h"

#include "Aabb.h"

import <limits>;

bool Ray::Intersects(const Aabb& box, Float& t, Float epsilon) const
{
	Float tMax = std::numeric_limits<Float>::max();;
	Float tMin = -tMax;

	if (!(
		IntersectsAxis(Start.X, Direction.X, box.Min.X, box.Max.X, tMin, tMax, epsilon) &&
		IntersectsAxis(Start.Y, Direction.Y, box.Min.Y, box.Max.Y, tMin, tMax, epsilon) &&
		IntersectsAxis(Start.Z, Direction.Z, box.Min.Z, box.Max.Z, tMin, tMax, epsilon)
		) || tMax < 0)
		return false;

	t = std::max(0.0, tMin);

	return true;
}

bool Ray::IntersectsAxis(Float start, Float direction, Float min, Float max, Float& tMin, Float& tMax, Float epsilon) const
{
	if (direction < -epsilon || direction > epsilon)
	{
		Float t1 = (min - start) / direction;
		Float t2 = (max - start) / direction;

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