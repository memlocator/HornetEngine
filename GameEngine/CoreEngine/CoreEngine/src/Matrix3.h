/*
Matrix.H
Author: 
9/16/16

contains declaration of Matrix class
*/

#pragma once

#include "Vector3.h"

class Matrix3
{
public:
	float Data[4][4] = { {} };

	constexpr Matrix3()
	{
		Identity();
	}
	constexpr Matrix3(float x, float y, float z)
	{
		Translate(x, y, z);
	}
	constexpr Matrix3(const Vector3& vector)
	{
		Translate(vector);
	}
	constexpr Matrix3(const Vector3& position, const Vector3& right, const Vector3& up, const Vector3& front)
	{
		SetVectors(position, right, up, front);
	}
	Matrix3(const Vector3& position, const Vector3& direction, const Vector3& globalUp = Vector3(0, 1, 0));
	constexpr Matrix3(const Matrix3& mat)
	{
		for (int i = 0; i < 16; ++i)
			Data[i % 4][i / 4] = mat.Data[i % 4][i / 4];
	}

	constexpr Matrix3& Identity()
	{
		for (int i = 0; i < 16; i++)
			Data[i % 4][i / 4] = i % 4 == i / 4;

		return *this;
	}
	Matrix3& Transpose();
	constexpr Matrix3& SetVectors(const Vector3& position, const Vector3& right, const Vector3& up, const Vector3& front)
	{
		Translate(position);

		Data[0][0] = right.X;
		Data[1][0] = right.Y;
		Data[2][0] = right.Z;

		Data[0][1] = up.X;
		Data[1][1] = up.Y;
		Data[2][1] = up.Z;

		Data[0][2] = front.X;
		Data[1][2] = front.Y;
		Data[2][2] = front.Z;

		return *this;
	}
	Matrix3& SetRight(const Vector3& vector);
	Matrix3& SetUp(const Vector3& vector);
	Matrix3& SetFront(const Vector3& vector);
	Matrix3& SetTranslation(const Vector3& vector);
	Matrix3& SetTransformedTranslation(const Vector3& vector);
	constexpr Matrix3& Translate(float x, float y, float z)
	{
		Identity();

		Data[0][3] = x;
		Data[1][3] = y;
		Data[2][3] = z;

		return *this;
	}
	constexpr Matrix3& Translate(const Vector3& vector)
	{
		return Translate(vector.X, vector.Y, vector.Z);
	}
	Matrix3& Scale(float x, float y, float z);
	Matrix3& Scale(const Vector3& vector);
	Matrix3& RotateAxis(const Vector3& axis, float theta);
	Matrix3& RotatePitch(float theta);
	Matrix3& RotateYaw(float theta);
	Matrix3& RotateRoll(float theta);
	Matrix3& RotateEulerAngles(float pitch, float yaw, float roll);
	Matrix3& RotateEulerAnglesYaw(float yaw, float pitch, float roll);
	Matrix3& Inverse();
	Matrix3& Invert(const Matrix3& other);
	Matrix3& Projection(float distance, float near, float far, float width, float height);
	Matrix3& ExtractRotation(const Matrix3& matrix, const Vector3& newTranslation = Vector3());
	Matrix3& TransformAround(const Vector3& point);
	Matrix3& Face(const Vector3& position, const Vector3& direction, const Vector3& globalUp = Vector3(0, 1, 0));

	Matrix3 Transposed() const { return Matrix3(*this).Transpose(); }
	Matrix3 Inverted() const { return Matrix3(*this).Inverse(); }
	Matrix3 Rotation(const Vector3& newTranslation = Vector3()) const { return Matrix3().ExtractRotation(*this, newTranslation); }
	Matrix3 TransformedAround(const Vector3& point) const { return Matrix3(*this).TransformAround(point); }

	Vector3 RightVector() const;
	Vector3 UpVector() const;
	Vector3 FrontVector() const;
	Vector3 Translation() const;
	Vector3 ExtractScale() const;
	float Det() const;

	Matrix3  operator+(const Matrix3& other) const;
	Matrix3  operator-(const Matrix3& other) const;
	Matrix3  operator-() const;
	Matrix3  operator*(const Matrix3& other) const;
	Vector3  operator*(const Vector3& other) const;
	Matrix3  operator*(float scalar) const;

	Matrix3 FullMultiply(const Matrix3& other) const;

	float* operator[](int row);
	const float* operator[](int row) const;

	operator std::string() const;

	Matrix3& operator=(const Matrix3& other);
	Matrix3& operator+=(const Matrix3& other);
	Matrix3& operator-=(const Matrix3& other);
	Matrix3& operator*=(const Matrix3& other);
	Matrix3& operator*=(float scalar);

	bool operator==(const Matrix3& other) const;
	bool operator!=(const Matrix3& other) const;

	static Matrix3 NewScale(float x, float y, float z) { return Matrix3().Scale(x, y, z); }
	static Matrix3 NewScale(const Vector3& vector) { return Matrix3().Scale(vector); }
	static Matrix3 AxisRotation(const Vector3& axis, float theta) { return Matrix3().RotateAxis(axis, theta); }
	static Matrix3 PitchRotation(float theta) { return Matrix3().RotatePitch(theta); }
	static Matrix3 YawRotation(float theta) { return Matrix3().RotateYaw(theta); }
	static Matrix3 RollRotation(float theta) { return Matrix3().RotateRoll(theta); }
	static Matrix3 EulerAnglesRotation(float pitch, float yaw, float roll) { return Matrix3().RotateEulerAngles(pitch, yaw, roll); }
	static Matrix3 EulerAnglesYawRotation(float yaw, float pitch, float roll) { return Matrix3().RotateEulerAnglesYaw(yaw, pitch, roll); }
	static Matrix3 NewProjection(float distance, float nearPlane, float farPlane, float width, float height) { return Matrix3().Projection(distance, nearPlane, farPlane, width, height); }
	static Matrix3 Facing(const Vector3& position, const Vector3& direction, const Vector3& globalUp = Vector3(0, 1, 0)) { return Matrix3().Face(position, direction, globalUp); }

private:
	static bool Compare(float x, float y, float epsilon);

	float Det(int y1, int y2, int x1, int x2) const;
	float ComponentMultiplication(const Matrix3& rhs, int x, int y) const;
	float ComponentMultiplicationNoAffine(const Matrix3& rhs, int x, int y) const;
};

constexpr Matrix3 operator*(float scalar, const Matrix3& matrix)
{
	Matrix3 result;

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			result.Data[y][x] = scalar * matrix.Data[y][x];

	return result;
}
std::ostream& operator<<(std::ostream& out, const Matrix3& matrix);
