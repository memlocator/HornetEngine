#include "RGBA.h"

#include <sstream>

RGBA& RGBA::Set(float r, float g, float b, float a)
{
	R = r;
	G = g;
	B = b;
	A = a;

	return *this;
}

RGBA RGBA::Lerp(const RGBA& end, float t) const
{
	return RGBA(
		(1 - t) * R + t * end.R,
		(1 - t) * G + t * end.G,
		(1 - t) * B + t * end.B,
		(1 - t) * A + t * end.A
	);
}

unsigned int RGBA::ARGB() const
{
	return (
		(int(A * 255) << 24) +
		(int(R * 255) << 16) +
		(int(G * 255) << 8) +
		int(B * 255)
		);
}

unsigned int RGBA::ABGR() const
{
	return (
		(int(A * 255) % 256 << 24) +
		(int(B * 255) % 256 << 16) +
		(int(G * 255) % 256 << 8) +
		int(R * 255) % 256
		);
}

bool RGBA::operator==(const RGBA& color) const
{
	return (R == color.R) && (G == color.G) && (B == color.B) && (A == color.A);
}

bool RGBA::operator!=(const RGBA& color) const
{
	return !(*this == color);
}

RGBA::operator unsigned int() const
{
	return (
		(int(R * 255) << 24) +
		(int(G * 255) << 16) +
		(int(B * 255) << 8) +
		int(A * 255)
		);
}

RGBA::operator Vector3() const
{
	return Vector3((Float)R, (Float)G, (Float)B, (Float)A);
}

RGBA& RGBA::operator=(const RGBA& other)
{
	Set(other.R, other.G, other.B, other.A);

	return *this;
}

RGBA::operator std::string() const
{
	std::stringstream out;

	out << *this;

	return out.str();
}

std::ostream& operator<<(std::ostream& out, const RGBA& color)
{
	return out << "{ R: " << color.R << ", G: " << color.G << ", B: " << color.B << ", A: " << color.A << " }";
}