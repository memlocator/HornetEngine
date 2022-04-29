#include "Vector2.h"

#include <iostream>
#include <sstream>

Vector2F operator*(float scalar, const Vector2F& vector) { return vector * scalar; }
Vector2D operator*(double scalar, const Vector2D& vector) { return vector * scalar; }
Vector2I operator*(int scalar, const Vector2I& vector) { return vector * scalar; }

std::ostream& operator<<(std::ostream& out, const Vector2F& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << ", " << vector.Z << " >";
}

std::ostream& operator<<(std::ostream& out, const Vector2D& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << ", " << vector.Z << " >";
}

std::ostream& operator<<(std::ostream& out, const Vector2I& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << ", " << vector.Z << " >";
}

template <>
Vector2Type<float, float>::operator std::string() const
{
	std::stringstream out;
	out << *this;

	return out.str();
}

template <>
Vector2Type<double, double>::operator std::string() const
{
	std::stringstream out;
	out << *this;

	return out.str();
}

template <>
Vector2Type<int, float>::operator std::string() const
{
	std::stringstream out;
	out << *this;

	return out.str();
}