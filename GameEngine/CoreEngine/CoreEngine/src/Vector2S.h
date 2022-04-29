#pragma once

#include <iosfwd>
#include <string>
#include <cmath>

#include "Precision.h"

template <typename Number, typename DistanceType>
class Vector2SType
{
public:
	Number X, Y;

	constexpr Vector2SType() : X(0), Y(0) {}
	constexpr Vector2SType(Number x, Number y = 0) : X(x), Y(y) {}
	constexpr Vector2SType(const Vector2SType<float, float>& other) : X((Number)other.X), Y((Number)other.Y) {}
	constexpr Vector2SType(const Vector2SType<double, double>& other) : X((Number)other.X), Y((Number)other.Y) {}
	constexpr Vector2SType(const Vector2SType<int, float>& other) : X((Number)other.X), Y((Number)other.Y) {}

	Vector2SType& Set(Number x, Number y = 0)
	{
		X = x; Y = y;
		return *this;
	}
	Vector2SType& Normalize()
	{
		return *this *= (Number)(1 / Length());
	}
	DistanceType Dot(const Vector2SType& other) const
	{
		return (DistanceType)(X * other.X + Y * other.Y);
	}
	Vector2SType Unit() const
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
	Vector2SType& InvertLength()
	{
		return *this *= (Number)(1 / SquareLength());
	}

	Vector2SType InvertedLength() const
	{
		return *this * (Number)(1 / SquareLength());
	}
	Vector2SType& Scale(const Vector2SType& other)
	{
		return Scale(other.X, other.Y);
	}
	Vector2SType& Scale(Number x, Number y)
	{
		return Set(X * x, Y * y);
	}

	Vector2SType Negate() const { return -*this; }

	Vector2SType operator-() const
	{
		return Vector2SType(-X, -Y);
	}
	Vector2SType operator+(const Vector2SType& other) const
	{
		return Vector2SType(X + other.X, Y + other.Y);
	}
	Vector2SType operator-(const Vector2SType& other) const
	{
		return Vector2SType(X - other.X, Y - other.Y);
	}
	Vector2SType operator*(Number scalar) const
	{
		return Vector2SType(X * scalar, Y * scalar);
	}
	DistanceType operator*(const Vector2SType& other) const
	{
		return Dot(other);
	}
	Vector2SType& operator=(const Vector2SType& other)
	{
		return Set(other.X, other.Y);
	}
	Vector2SType& operator+=(const Vector2SType& other)
	{
		return Set(X + other.X, Y + other.Y);
	}
	Vector2SType& operator-=(const Vector2SType& other)
	{
		return Set(X - other.X, Y - other.Y);
	}
	Vector2SType& operator*=(Number scalar)
	{
		return Set(X * scalar, Y * scalar);
	}
	bool operator==(const Vector2SType& other) const
	{
		return Compare(X, other.X) && Compare(Y, other.Y);
	}
	bool operator!=(const Vector2SType& other) const
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

using Vector2SF = Vector2SType<float, float>;
using Vector2SD = Vector2SType<double, double>;
using Vector2SI = Vector2SType<int, float>;
using Vector2S = Vector2SType<Float, Float>;

Vector2SF operator*(float scalar, const Vector2SF& vector);
Vector2SD operator*(double scalar, const Vector2SD& vector);
Vector2SI operator*(int scalar, const Vector2SI& vector);

std::ostream& operator<<(std::ostream& out, const Vector2SF& vector);
std::ostream& operator<<(std::ostream& out, const Vector2SD& vector);
std::ostream& operator<<(std::ostream& out, const Vector2SI& vector);

template <>
Vector2SType<float, float>::operator std::string() const;

template <>
Vector2SType<double, double>::operator std::string() const;

template <>
Vector2SType<int, float>::operator std::string() const;