#include "Vector2S.h"

#include <iostream>
#include <sstream>

Vector2SF operator*(float scalar, const Vector2SF& vector) { return vector * scalar; }
Vector2SD operator*(double scalar, const Vector2SD& vector) { return vector * scalar; }
Vector2SI operator*(int scalar, const Vector2SI& vector) { return vector * scalar; }

std::ostream& operator<<(std::ostream& out, const Vector2SF& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << " >";
}

std::ostream& operator<<(std::ostream& out, const Vector2SD& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << " >";
}

std::ostream& operator<<(std::ostream& out, const Vector2SI& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << " >";
}

template <>
Vector2SType<float, float>::operator std::string() const
{
	std::stringstream out;
	out << *this;

	return out.str();
}

template <>
Vector2SType<double, double>::operator std::string() const
{
	std::stringstream out;
	out << *this;

	return out.str();
}

template <>
Vector2SType<int, float>::operator std::string() const
{
	std::stringstream out;
	out << *this;

	return out.str();
}