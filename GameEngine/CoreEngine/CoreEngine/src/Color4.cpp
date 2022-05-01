#include "Color4.h"

import <sstream>;

Color4& Color4::Set(float r, float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;

	return *this;
}

Color4 Color4::Lerp(const Color4& end, float t) const
{
	return Color4(
		(1 - t) * R + t * end.R,
		(1 - t) * G + t * end.G,
		(1 - t) * B + t * end.B,
		(1 - t) * A + t * end.A
	);
}

unsigned int Color4::ARGB() const
{
	return (
		(int(A * 255) << 24) +
		(int(R * 255) << 16) +
		(int(G * 255) << 8) +
		int(B * 255)
		);
}

unsigned int Color4::ABGR() const
{
	return (
		(int(A * 255) % 256 << 24) +
		(int(B * 255) % 256 << 16) +
		(int(G * 255) % 256 << 8) +
		int(R * 255) % 256
		);
}

bool Color4::operator==(const Color4& color) const
{
	return (R == color.R) && (G == color.G) && (B == color.B) && (A == color.A);
}

bool Color4::operator!=(const Color4& color) const
{
	return !(*this == color);
}

Color4::operator unsigned int() const
{
	return (
		(int(R * 255) << 24) +
		(int(G * 255) << 16) +
		(int(B * 255) << 8) +
		int(A * 255)
		);
}

Color4::operator Vector3() const
{
	return Vector3((Float)R, (Float)G, (Float)B, (Float)A);
}

Color4& Color4::operator=(const Color4& other)
{
	Set(other.R, other.G, other.B, other.A);

	return *this;
}

Color4::operator std::string() const
{
	std::stringstream out;

	out << *this;

	return out.str();
}

std::ostream& operator<<(std::ostream& out, const Color4& color)
{
	return out << "{ R: " << color.R << ", G: " << color.G << ", B: " << color.B << ", A: " << color.A << " }";
}