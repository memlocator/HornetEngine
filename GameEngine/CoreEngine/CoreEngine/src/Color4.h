#pragma once

#include "Vector3.h"

struct Color4
{
	float R, G, B, A;

	constexpr Color4() : R(1), G(1), B(1), A(1) {}
	constexpr Color4(float r, float g, float b, float a = 1) : R(r), G(g), B(b), A(a) {}
	constexpr Color4(double r, double g, double b, double a = 1) : R((float)r), G((float)g), B((float)b), A((float)a) {}
	constexpr Color4(unsigned int color)
	{
		R = float((color >> 24) & 0xFF) / 255.0f;
		G = float((color >> 16) & 0xFF) / 255.0f;
		B = float((color >> 8) & 0xFF) / 255.0f;
		A = float(color & 0xFF) / 255.0f;
	}
	constexpr Color4(const Vector3& vector) : R(float(vector.X)), G(float(vector.Y)), B(float(vector.Z)), A(float(vector.W)) {}

	Color4& Set(float r = 1, float g = 1, float b = 1, float a = 1);
	Color4 Lerp(const Color4& end, float t) const;
	unsigned int ARGB() const;
	unsigned int ABGR() const;

	bool operator==(const Color4& color) const;
	bool operator!=(const Color4& color) const;

	operator unsigned int() const;
	operator Vector3() const;
	operator std::string() const;
	Color4& operator=(const Color4& other);
};

std::ostream& operator<<(std::ostream& out, const Color4& color);
