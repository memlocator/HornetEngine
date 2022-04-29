#pragma once

#include <iosfwd>
#include <string>
#include <cmath>

#include "Precision.h"

template <typename Number, typename DistanceType>
class Vector3Type
{
public:
	Number X, Y, Z, W;

	constexpr Vector3Type() : X(0), Y(0), Z(0), W(0) {}
	constexpr Vector3Type(Number x, Number y = 0, Number z = 0, Number w = 0) : X(x), Y(y), Z(z), W(w) {}
	constexpr Vector3Type(const Vector3Type<float, float>& other) : X((Number)other.X), Y((Number)other.Y), Z((Number)other.Z), W((Number)other.W) {}
	constexpr Vector3Type(const Vector3Type<double, double>& other) : X((Number)other.X), Y((Number)other.Y), Z((Number)other.Z), W((Number)other.W) {}
	constexpr Vector3Type(const Vector3Type<int, float>& other) : X((Number)other.X), Y((Number)other.Y), Z((Number)other.Z), W((Number)other.W) {}

	Vector3Type& Set(Number x, Number y = 0, Number z = 0, Number w = 0)
	{
		X = x; Y = y; Z = z; W = w;
		return *this;
	}
	Vector3Type& Normalize()
	{
		return *this *= (Number)(1 / Length());
	}
	DistanceType Dot(const Vector3Type& other) const
	{
		return (DistanceType)(X * other.X + Y * other.Y + Z * other.Z);
	}
	Vector3Type Cross(const Vector3Type& other) const
	{
		return Vector3Type(
			Y * other.Z - Z * other.Y,
			Z * other.X - X * other.Z,
			X * other.Y - Y * other.X
		);
	}
	Vector3Type Unit() const
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
	Vector3Type& Scale(const Vector3Type& other)
	{
		return Scale(other.X, other.Y, other.Z, other.W);
	}
	Vector3Type& Scale(Number x, Number y, Number z, Number w = 1)
	{
		return Set(X * x, Y * y, Z * z, W * w);
	}
	Vector3Type& InvertLength()
	{
		return *this *= (Number)(1 / SquareLength());
	}

	Vector3Type InvertedLength() const
	{
		return *this * (Number)(1 / SquareLength());
	}

	Vector3Type Negate() const { return -*this; }

	Vector3Type operator-() const
	{
		return Vector3Type(-X, -Y, -Z, -W);
	}
	Vector3Type operator+(const Vector3Type& other) const
	{
		return Vector3Type(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
	}
	Vector3Type operator-(const Vector3Type& other) const
	{
		return Vector3Type(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
	}
	Vector3Type operator*(Number scalar) const
	{
		return Vector3Type(X * scalar, Y * scalar, Z * scalar, W * scalar);
	}
	DistanceType operator*(const Vector3Type& other) const
	{
		return Dot(other);
	}
	Vector3Type& operator=(const Vector3Type& other)
	{
		return Set(other.X, other.Y, other.Z, other.W);
	}
	Vector3Type& operator+=(const Vector3Type& other)
	{
		return Set(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
	}
	Vector3Type& operator-=(const Vector3Type& other)
	{
		return Set(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
	}
	Vector3Type& operator*=(Number scalar)
	{
		return Set(X * scalar, Y * scalar, Z * scalar, W * scalar);
	}
	bool operator==(const Vector3Type& other) const
	{
		return Compare(X, other.X) && Compare(Y, other.Y) && Compare(Z, other.Z) && Compare(W, other.W);
	}
	bool operator!=(const Vector3Type& other) const
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

using Vector3F = Vector3Type<float, float>;
using Vector3D = Vector3Type<double, double>;
using Vector3I = Vector3Type<int, float>;
using Vector3 = Vector3Type<Float, Float>;

Vector3F operator*(float scalar, const Vector3F& vector);
Vector3D operator*(double scalar, const Vector3D& vector);
Vector3I operator*(int scalar, const Vector3I& vector);

std::ostream& operator<<(std::ostream& out, const Vector3F& vector);
std::ostream& operator<<(std::ostream& out, const Vector3D& vector);
std::ostream& operator<<(std::ostream& out, const Vector3I& vector);

template <>
Vector3Type<float, float>::operator std::string() const;

template <>
Vector3Type<double, double>::operator std::string() const;

template <>
Vector3Type<int, float>::operator std::string() const;