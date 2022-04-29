#pragma once

#include <iosfwd>
#include <string>
#include <cmath>

#include "Precision.h"

template <typename Number, typename DistanceType>
class Vector2Type
{
public:
	Number X, Y, Z;

	constexpr Vector2Type() : X(0), Y(0), Z(0) {}
	constexpr Vector2Type(Number x, Number y = 0, Number z = 0) : X(x), Y(y), Z(z) {}
	constexpr Vector2Type(const Vector2Type<float, float>& other) : X((Number)other.X), Y((Number)other.Y), Z((Number)other.Z) {}
	constexpr Vector2Type(const Vector2Type<double, double>& other) : X((Number)other.X), Y((Number)other.Y), Z((Number)other.Z) {}
	constexpr Vector2Type(const Vector2Type<int, float>& other) : X((Number)other.X), Y((Number)other.Y), Z((Number)other.Z) {}

	Vector2Type& Set(Number x, Number y = 0, Number z = 0)
	{
		X = x; Y = y; Z = z;
		return *this;
	}
	Vector2Type& Normalize()
	{
		return *this *= (Number)(1 / Length());
	}
	DistanceType Dot(const Vector2Type& other) const
	{
		return (DistanceType)(X * other.X + Y * other.Y);
	}
	Vector2Type Unit() const
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
	Vector2Type& InvertLength()
	{
		return *this *= (Number)(1 / SquareLength());
	}

	Vector2Type InvertedLength() const
	{
		return *this * (Number)(1 / SquareLength());
	}
	Vector2Type& Scale(const Vector2Type& other)
	{
		return Scale(other.X, other.Y, other.Z);
	}
	Vector2Type& Scale(Number x, Number y, Number z)
	{
		return Set(X * x, Y * y, Z * z);
	}

	Vector2Type Negate() const { return -*this; }

	Vector2Type operator-() const
	{
		return Vector2Type(-X, -Y, -Z);
	}
	Vector2Type operator+(const Vector2Type& other) const
	{
		return Vector2Type(X + other.X, Y + other.Y, Z + other.Z);
	}
	Vector2Type operator-(const Vector2Type& other) const
	{
		return Vector2Type(X - other.X, Y - other.Y, Z - other.Z);
	}
	Vector2Type operator*(Number scalar) const
	{
		return Vector2Type(X * scalar, Y * scalar, Z * scalar);
	}
	DistanceType operator*(const Vector2Type& other) const
	{
		return Dot(other);
	}
	Vector2Type& operator=(const Vector2Type& other)
	{
		return Set(other.X, other.Y, other.Z);
	}
	Vector2Type& operator+=(const Vector2Type& other)
	{
		return Set(X + other.X, Y + other.Y, Z + other.Z);
	}
	Vector2Type& operator-=(const Vector2Type& other)
	{
		return Set(X - other.X, Y - other.Y, Z - other.Z);
	}
	Vector2Type& operator*=(Number scalar)
	{
		return Set(X * scalar, Y * scalar, Z * scalar);
	}
	bool operator==(const Vector2Type& other) const
	{
		return Compare(X, other.X) && Compare(Y, other.Y) && Compare(Z, other.Z);
	}
	bool operator!=(const Vector2Type& other) const
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

using Vector2F = Vector2Type<float, float>;
using Vector2D = Vector2Type<double, double>;
using Vector2I = Vector2Type<int, float>;
using Vector2 = Vector2Type<Float, Float>;

Vector2F operator*(float scalar, const Vector2F& vector);
Vector2D operator*(double scalar, const Vector2D& vector);
Vector2I operator*(int scalar, const Vector2I& vector);

std::ostream& operator<<(std::ostream& out, const Vector2F& vector);
std::ostream& operator<<(std::ostream& out, const Vector2D& vector);
std::ostream& operator<<(std::ostream& out, const Vector2I& vector);

template <>
Vector2Type<float, float>::operator std::string() const;

template <>
Vector2Type<double, double>::operator std::string() const;

template <>
Vector2Type<int, float>::operator std::string() const;