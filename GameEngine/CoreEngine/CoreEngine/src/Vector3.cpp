/*
Vector.Cpp

contains implimentation of Vector class functions
*/
#include "Vector3.h"

#include <iostream>
extern "C" {
#include <stdlib.h>
}
#include <sstream>
extern "C" {
#include <math.h>
}


// set coordinates
Vector3& Vector3::Set(Float x, Float y, Float z, Float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;

	return *this;
}

// normalizes the vector
Vector3& Vector3::Normalize()
{
	Float length = Length();

	if (cmath::abs(length) < 1e-9f)
		return *this;

	length = 1 / length;

	X *= length;
	Y *= length;
	Z *= length;

	return *this;
}

Float Vector3::Dot(const Vector3& other) const
{
	return *this * other;
}

// calculates the cross product between two vectors
Vector3 Vector3::Cross(const Vector3& other) const
{
	return Vector3(
		Y * other.Z - Z * other.Y,
		Z * other.X - X * other.Z,
		X * other.Y - Y * other.X
	);
}

Vector3 Vector3::Unit() const
{
	return Vector3(*this).Normalize();
}

// returns the length of the vector
Float Vector3::Length() const
{
	return std::sqrt(SquareLength());
}

// returns the square length of the vector
Float Vector3::SquareLength() const
{
	return X * X + Y * Y + Z * Z + W * W;
}

Vector3& Vector3::Scale(const Vector3& other)
{
	X *= other.X;
	Y *= other.Y;
	Z *= other.Z;

	return *this;
}

Vector3& Vector3::Scale(Float x, Float y, Float z)
{
	X *= x;
	Y *= y;
	Z *= z;

	return *this;
}

Vector3& Vector3::InvertLength()
{
	Float scale = 1.f / SquareLength();

	X *= scale;
	Y *= scale;
	Z *= scale;

	return *this;
}

Vector3 Vector3::InvertedLength() const
{
	return Vector3(*this).InvertLength();
}

// negation
Vector3 Vector3::operator-() const
{
	return Vector3(-X, -Y, -Z, -W);
}

// addition
Vector3 Vector3::operator+(const Vector3& other) const
{
	return Vector3(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
}

// subtraction
Vector3 Vector3::operator-(const Vector3& other) const
{
	return Vector3(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
}

// scalar multiplication
Vector3 Vector3::operator*(Float scalar) const
{
	return Vector3(scalar * X, scalar * Y, scalar * Z, scalar * W);
}

// dot product multiplication
Float Vector3::operator*(const Vector3& other) const
{
	return X * other.X + Y * other.Y + Z * other.Z + W * other.W;
}

// assignment
Vector3& Vector3::operator=(const Vector3& other)
{
	X = other.X;
	Y = other.Y;
	Z = other.Z;
	W = other.W;

	return *this;
}

// addition assignment
Vector3& Vector3::operator+=(const Vector3& other)
{
	*this = *this + other;

	return *this;
}

// subtraction assignment
Vector3& Vector3::operator-=(const Vector3& other)
{
	*this = *this - other;

	return *this;
}

// multiplication assignment
Vector3& Vector3::operator*=(Float scalar)
{
	*this = *this * scalar;

	return *this;
}

bool Vector3::Compare(Float x, Float y, Float epsilon) const
{
	return cmath::abs(x - y) < epsilon;
}

bool Vector3::operator==(const Vector3& other) const
{
	Float epsilon = 1e-5f;

	return Compare(X, other.X, epsilon) && Compare(Y, other.Y, epsilon) && Compare(Z, other.Z, epsilon);
}

bool Vector3::operator!=(const Vector3& other) const
{
	return !(*this == other);
}

Float Vector3::operator[](int i) const
{
	return ((const Float*)(this))[i];
}

Float& Vector3::operator[](int i)
{
	return ((Float*)(this))[i];
}

// rhs scalar multiplication
Vector3 operator*(Float scalar, const Vector3& vector)
{
	//use other scalar multiplication function
	return vector * scalar;
}

Vector3::operator std::string() const
{
	std::stringstream out;

	out << *this;

	return out.str();
}

// stream output
std::ostream& operator<<(std::ostream& out, const Vector3& vector)
{
	if (vector.W < 0.99999 || vector.W > 1.00001)
		out << "< " << vector.X << ", " << vector.Y << ", " << vector.Z << ", " << vector.W << " >";
	else
		out << "( " << vector.X << ", " << vector.Y << ", " << vector.Z << " )";
		
	return out;
}
