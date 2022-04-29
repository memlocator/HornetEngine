#pragma once

#include <iosfwd>
#include <string>
#include <cmath>

#include "Precision.h"

template <typename Number, typename DistanceType>
class Vector3SType
{
public:
	Number X, Y, Z;

	constexpr Vector3SType() : X(0), Y(0), Z(0) {}
	constexpr Vector3SType(Number x, Number y = 0, Number z = 0) : X(x), Y(y), Z(z) {}
	constexpr Vector3SType(const Vector3SType<float, float>& other) : X((Number)other.X), Y((Number)other.Y), Z((Number)other.Z) {}
	constexpr Vector3SType(const Vector3SType<double, double>& other) : X((Number)other.X), Y((Number)other.Y), Z((Number)other.Z) {}
	constexpr Vector3SType(const Vector3SType<int, float>& other) : X((Number)other.X), Y((Number)other.Y), Z((Number)other.Z) {}

	Vector3SType& Set(Number x, Number y = 0, Number z = 0)
	{
		X = x; Y = y; Z = z;
		return *this;
	}
	Vector3SType& Normalize()
	{
		return *this *= (Number)(1 / Length());
	}
	DistanceType Dot(const Vector3SType& other) const
	{
		return (DistanceType)(X * other.X + Y * other.Y + Z * other.Z);
	}
	Vector3SType Cross(const Vector3SType& other) const
	{
		return Vector3SType(
			Y * other.Z - Z * other.Y,
			Z * other.X - X * other.Z,
			X * other.Y - Y * other.X
		);
	}
	Vector3SType Unit() const
	{
		return (Number)(1 / Length()) * *this;
	}
	DistanceType Length() const
	{
		return std::sqrt(SquareLength());
	}
	DistanceType SquareLength() const
	{
		return Dot(*this);
	}
	Vector3SType& Scale(const Vector3SType& other)
	{
		return Scale(other.X, other.Y, other.Z);
	}
	Vector3SType& Scale(Number x, Number y, Number z)
	{
		return Set(X * x, Y * y, Z * z);
	}
	Vector3SType& InvertLength()
	{
		return *this *= (Number)(1 / SquareLength());
	}

	Vector3SType InvertedLength() const
	{
		return *this * (Number)(1 / SquareLength());
	}

	Vector3SType Negate() const { return -*this; }

	Vector3SType operator-() const
	{
		return Vector3SType(-X, -Y, -Z);
	}
	Vector3SType operator+(const Vector3SType& other) const
	{
		return Vector3SType(X + other.X, Y + other.Y, Z + other.Z);
	}
	Vector3SType operator-(const Vector3SType& other) const
	{
		return Vector3SType(X - other.X, Y - other.Y, Z - other.Z);
	}
	Vector3SType operator*(Number scalar) const
	{
		return Vector3SType(X * scalar, Y * scalar, Z * scalar);
	}
	DistanceType operator*(const Vector3SType& other) const
	{
		return Dot(other);
	}
	Vector3SType& operator=(const Vector3SType& other)
	{
		return Set(other.X, other.Y, other.Z);
	}
	Vector3SType& operator+=(const Vector3SType& other)
	{
		return Set(X + other.X, Y + other.Y, Z + other.Z);
	}
	Vector3SType& operator-=(const Vector3SType& other)
	{
		return Set(X - other.X, Y - other.Y, Z - other.Z);
	}
	Vector3SType& operator*=(Number scalar)
	{
		return Set(X * scalar, Y * scalar, Z * scalar);
	}
	bool operator==(const Vector3SType& other) const
	{
		return Compare(X, other.X) && Compare(Y, other.Y) && Compare(Z, other.Z);
	}
	bool operator!=(const Vector3SType& other) const
	{
		return !(*this == other);
	}
	Number operator[](int i) const
	{
		return (&X)[i];
	}
	Number& operator[](int i)
	{
		return (&X)[i];
	}

	operator std::string() const;

private:
	bool Compare(Number x, Number y, Number epsilon = (Number)1e-5) const
	{
		return std::abs(x - y) < epsilon;
	}
};

using Vector3SF = Vector3SType<float, float>;
using Vector3SD = Vector3SType<double, double>;
using Vector3SI = Vector3SType<int, float>;
using Vector3S = Vector3SType<Float, Float>;

Vector3SF operator*(float scalar, const Vector3SF& vector);
Vector3SD operator*(double scalar, const Vector3SD& vector);
Vector3SI operator*(int scalar, const Vector3SI& vector);

std::ostream& operator<<(std::ostream& out, const Vector3SF& vector);
std::ostream& operator<<(std::ostream& out, const Vector3SD& vector);
std::ostream& operator<<(std::ostream& out, const Vector3SI& vector);

template <>
Vector3SType<float, float>::operator std::string() const;

template <>
Vector3SType<double, double>::operator std::string() const;

template <>
Vector3SType<int, float>::operator std::string() const;