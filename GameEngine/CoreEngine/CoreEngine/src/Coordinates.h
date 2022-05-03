#pragma once

#include "Math/Vector3.h"

import <cmath>;

namespace Engine
{
	struct Coordinates
	{
		int X = 0;
		int Y = 0;
		int Z = 0;

		constexpr Coordinates(int x = 0, int y = 0, int z = 0) : X(x), Y(y), Z(z) {}
		Coordinates(const Vector3& vector) : X(int(std::floor(vector.X))), Y(int(std::floor(vector.Y))), Z(int(std::floor(vector.Z))) {}

		operator Vector3() const { return Vector3(Float(X), Float(Y), Float(Z)); }

		Coordinates operator+(const Coordinates& c) { return Coordinates(X + c.X, Y + c.Y, Z + c.Z); }
	};

	Coordinates operator*(int x, const Coordinates& coords);
}