/*
Vector3.H

contains declaration of Vector3 class
*/

#pragma once

#include <iosfwd>
#include <string>

#include "ConstMath.h"
#include "Precision.h"

class Vector3
{
public:
	Float X, Y, Z, W;

	constexpr Vector3(Float x = 0, Float y = 0, Float z = 0, Float w = 0) : X(x), Y(y), Z(z), W(w) {}
	constexpr Vector3(const Vector3& other) : X(other.X), Y(other.Y), Z(other.Z), W(other.W) {}

	Vector3& Set(Float x = 0, Float y = 0, Float z = 0, Float w = 0);
	Vector3& Normalize();
	Float Dot(const Vector3& other) const;
	Vector3 Cross(const Vector3& other) const;
	Vector3 Unit() const;
	Float Length() const;
	Float SquareLength() const;
	Vector3& Scale(const Vector3& other);
	Vector3& Scale(Float x, Float y, Float z);
	Vector3& InvertLength();

	Vector3 InvertedLength() const;
	Vector3 Negate() const { return -*this; }

	Vector3 operator-() const;
	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(Float scalar) const;
	Float operator*(const Vector3& other) const;
	Vector3& operator=(const Vector3& other);
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(Float scalar);
	bool operator==(const Vector3& other) const;
	bool operator!=(const Vector3& other) const;
	Float operator[](int i) const;
	Float& operator[](int i);

	operator std::string() const;

private:
	bool Compare(Float x, Float y, Float epsilon)  const;
};

Vector3 operator*(Float scalar, const Vector3& vector);
std::ostream& operator<<(std::ostream& out, const Vector3& vector);
