#pragma once

#include <string>

#include "Vector3.h"

struct Dimensions
{
	unsigned int Width;
	unsigned int Height;

	constexpr Dimensions(unsigned int width = 0, unsigned int height = 0) : Width(width), Height(height) {}
	Dimensions(const Vector3& size) : Width(unsigned int(size.X)), Height(unsigned int(size.Y)) {}

	operator std::string() const;
	bool operator==(const Dimensions& other) const { return Width == other.Width && Height == other.Height; }
	bool operator!=(const Dimensions& other) const { return Width != other.Width || Height != other.Height; }
};