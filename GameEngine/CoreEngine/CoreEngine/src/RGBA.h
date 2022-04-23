#pragma once

#include "Vector3.h"
#include "ObjectReflection.h"

struct RGBA
{
	float R, G, B, A;

	constexpr RGBA() : R(1), G(1), B(1), A(1) {}
	constexpr RGBA(float r, float g, float b, float a = 1) : R(r), G(g), B(b), A(a) {}
	constexpr RGBA(unsigned int color)
	{
		R = float((color >> 24) & 0xFF) / 255.0f;
		G = float((color >> 16) & 0xFF) / 255.0f;
		B = float((color >> 8) & 0xFF) / 255.0f;
		A = float(color & 0xFF) / 255.0f;
	}
	constexpr RGBA(const Vector3& vector) : R(vector.X), G(vector.Y), B(vector.Z), A(vector.W) {}

	RGBA& Set(float r = 1, float g = 1, float b = 1, float a = 1);
	RGBA Lerp(const RGBA& end, float t) const;
	unsigned int ARGB() const;
	unsigned int ABGR() const;

	bool operator==(const RGBA& color) const;
	bool operator!=(const RGBA& color) const;

	operator unsigned int() const;
	operator Vector3() const;
	operator std::string() const;
	RGBA& operator=(const RGBA& other);

	Base_Class;

	Reflected_Type(RGBA);
};

std::ostream& operator<<(std::ostream& out, const RGBA& color);

namespace Engine
{
	Define_Value_Type(RGBA);
}
