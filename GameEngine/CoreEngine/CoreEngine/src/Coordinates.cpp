#include "Coordinates.h"

namespace Engine
{
	Coordinates operator*(int x, const Coordinates& coords) { return Coordinates(coords.X * x, coords.Y * x, coords.Z * x); }
}