#pragma once

#include "Matrix3.h"

extern "C" {
#include <math.h>
}

class Quaternion
{
public:
	float X, Y, Z, W;

	constexpr Quaternion(float w = 0, float x = 0, float y = 0, float z = 0) : X(x), Y(y), Z(z), W(w) {}
	constexpr Quaternion(const Quaternion& quat) : X(quat.X), Y(quat.Y), Z(quat.Z), W(quat.W) {}
	constexpr Quaternion(const Vector3& vec) : X(vec.X), Y(vec.Y), Z(vec.Z), W(vec.W) {}
	Quaternion(const Vector3& axis, float angle);
	constexpr Quaternion(float w, const Vector3& vector) : X(vector.X), Y(vector.Y), Z(vector.Z), W(w) {}
	Quaternion(const Matrix3& matrix);

	Quaternion& Invert();
	Quaternion Inverse() const { return Quaternion(*this).Invert(); }
	Quaternion Slerp(const Quaternion& destination, float t) const;

	Quaternion operator*(const Quaternion& rhs) const;

	Matrix3 Matrix() const;

	Quaternion& Normalize();
	Quaternion Cross(const Quaternion& other) const;
	Quaternion Unit() const;
	float Length() const;
	float SquareLength() const;
	float Dot(const Quaternion& other) const;

	Quaternion operator-() const;
	Quaternion operator+(const Quaternion& other) const;
	Quaternion operator-(const Quaternion& other) const;
	Quaternion operator*(float scalar) const;
	Quaternion& operator=(const Quaternion& other);
	Quaternion& operator+=(const Quaternion& other);
	Quaternion& operator-=(const Quaternion& other);
	Quaternion& operator*=(float scalar);
	bool operator==(const Quaternion& other) const;
	bool operator!=(const Quaternion& other) const;
	float operator[](int i) const;
	float& operator[](int i);
	operator Vector3() const;
	operator std::string() const;

private:
	bool Compare(float x, float y, float epsilon) const;
};

Quaternion operator*(float scalar, const Quaternion& quaternion);
std::ostream& operator<<(std::ostream& out, const Quaternion& quaternion);
