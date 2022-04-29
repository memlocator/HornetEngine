#include "Vector3S.h"

#include <iostream>
#include <sstream>

Vector3SF operator*(float scalar, const Vector3SF& vector) { return vector * scalar; }
Vector3SD operator*(double scalar, const Vector3SD& vector) { return vector * scalar; }
Vector3SI operator*(int scalar, const Vector3SI& vector) { return vector * scalar; }

std::ostream& operator<<(std::ostream& out, const Vector3SF& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << ", " << vector.Z << " >";
}

std::ostream& operator<<(std::ostream& out, const Vector3SD& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << ", " << vector.Z << " >";
}

std::ostream& operator<<(std::ostream& out, const Vector3SI& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << ", " << vector.Z << " >";
}

template <>
Vector3SType<float, float>::operator std::string() const
{
	std::stringstream out;
	out << *this;

	return out.str();
}

template <>
Vector3SType<double, double>::operator std::string() const
{
	std::stringstream out;
	out << *this;

	return out.str();
}

template <>
Vector3SType<int, float>::operator std::string() const
{
	std::stringstream out;
	out << *this;

	return out.str();
}