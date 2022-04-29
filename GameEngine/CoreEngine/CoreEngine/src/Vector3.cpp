#include "Vector3.h"

#include <iostream>
#include <sstream>

Vector3F operator*(float scalar, const Vector3F& vector) { return vector * scalar; }
Vector3D operator*(double scalar, const Vector3D& vector) { return vector * scalar; }
Vector3I operator*(int scalar, const Vector3I& vector) { return vector * scalar; }

std::ostream& operator<<(std::ostream& out, const Vector3F& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << ", " << vector.Z << ", " << vector.W << " >";
}

std::ostream& operator<<(std::ostream& out, const Vector3D& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << ", " << vector.Z << ", " << vector.W << " >";
}

std::ostream& operator<<(std::ostream& out, const Vector3I& vector)
{
	return out << "< " << vector.X << ", " << vector.Y << ", " << vector.Z << ", " << vector.W << " >";
}

template <>
Vector3Type<float, float>::operator std::string() const
{
	std::stringstream out;
	out << *this;

	return out.str();
}

template <>
Vector3Type<double, double>::operator std::string() const
{
	std::stringstream out;
	out << *this;

	return out.str();
}

template <>
Vector3Type<int, float>::operator std::string() const
{
	std::stringstream out;
	out << *this;

	return out.str();
}