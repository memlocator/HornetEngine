/*
Matrix.H
Author: 
9/16/16

contains declaration of Matrix class
*/

#pragma once

#include "Vector3.h"
#include "Precision.h"

class Matrix4
{
public:
	Float Data[4][4] = { {} };

	constexpr Matrix4()
	{
		Identity();
	}
	constexpr Matrix4(bool) {}
	constexpr Matrix4(Float x, Float y, Float z)
	{
		Translate(x, y, z);
	}
	constexpr Matrix4(const Vector3& vector)
	{
		Translate(vector);
	}
	constexpr Matrix4(const Vector3& position, const Vector3& right, const Vector3& up, const Vector3& front)
	{
		SetVectors(position, right, up, front);
	}
	Matrix4(const Vector3& position, const Vector3& direction, const Vector3& globalUp = Vector3(0, 1, 0));
	constexpr Matrix4(const Matrix4& mat)
	{
		for (int i = 0; i < 16; ++i)
			Data[i % 4][i / 4] = mat.Data[i % 4][i / 4];
	}

	constexpr Matrix4& Identity()
	{
		for (int i = 0; i < 16; i++)
			Data[i % 4][i / 4] = i % 4 == i / 4;

		return *this;
	}
	Matrix4& Transpose();
	constexpr Matrix4& SetVectors(const Vector3& position, const Vector3& right, const Vector3& up, const Vector3& front)
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
	Matrix4& SetRight(const Vector3& vector);
	Matrix4& SetUp(const Vector3& vector);
	Matrix4& SetFront(const Vector3& vector);
	Matrix4& SetTranslation(const Vector3& vector);
	Matrix4& SetTransformedTranslation(const Vector3& vector);
	constexpr Matrix4& Translate(Float x, Float y, Float z)
	{
		Identity();

		Data[0][3] = x;
		Data[1][3] = y;
		Data[2][3] = z;

		return *this;
	}
	constexpr Matrix4& Translate(const Vector3& vector)
	{
		return Translate(vector.X, vector.Y, vector.Z);
	}
	Matrix4& Scale(Float x, Float y, Float z);
	Matrix4& Scale(const Vector3& vector);
	Matrix4& RotateAxis(const Vector3& axis, Float theta);
	Matrix4& RotatePitch(Float theta);
	Matrix4& RotateYaw(Float theta);
	Matrix4& RotateRoll(Float theta);
	Matrix4& RotateEulerAngles(Float pitch, Float yaw, Float roll);
	Matrix4& RotateEulerAnglesYaw(Float yaw, Float pitch, Float roll);
	Matrix4& Inverse();
	Matrix4& Invert(const Matrix4& other);
	Matrix4& Projection(Float distance, Float near, Float far, Float width, Float height);
	Matrix4& ExtractRotation(const Matrix4& matrix, const Vector3& newTranslation = Vector3());
	Matrix4& TransformAround(const Vector3& point);
	Matrix4& Face(const Vector3& position, const Vector3& direction, const Vector3& globalUp = Vector3(0, 1, 0));

	Matrix4 Transposed() const { return Matrix4(*this).Transpose(); }
	Matrix4 Inverted() const { return Matrix4(*this).Inverse(); }
	Matrix4 Rotation(const Vector3& newTranslation = Vector3()) const { return Matrix4(true).ExtractRotation(*this, newTranslation); }
	Matrix4 TransformedAround(const Vector3& point) const { return Matrix4(*this).TransformAround(point); }

	Vector3 RightVector() const;
	Vector3 UpVector() const;
	Vector3 FrontVector() const;
	Vector3 Translation() const;
	Vector3 ExtractScale() const;
	Float Det() const;

	Matrix4  operator+(const Matrix4& other) const;
	Matrix4  operator-(const Matrix4& other) const;
	Matrix4  operator-() const;
	Matrix4  operator*(const Matrix4& other) const;
	Vector3  operator*(const Vector3& other) const;
	Matrix4  operator*(Float scalar) const;

	Float* operator[](int row);
	const Float* operator[](int row) const;

	operator std::string() const;

	Matrix4& operator=(const Matrix4& other);
	Matrix4& operator+=(const Matrix4& other);
	Matrix4& operator-=(const Matrix4& other);
	Matrix4& operator*=(const Matrix4& other);
	Matrix4& operator*=(Float scalar);

	bool operator==(const Matrix4& other) const;
	bool operator!=(const Matrix4& other) const;

	static Matrix4 NewScale(Float x, Float y, Float z) { return Matrix4(true).Scale(x, y, z); }
	static Matrix4 NewScale(const Vector3& vector) { return Matrix4(true).Scale(vector); }
	static Matrix4 AxisRotation(const Vector3& axis, Float theta) { return Matrix4(true).RotateAxis(axis, theta); }
	static Matrix4 PitchRotation(Float theta) { return Matrix4(true).RotatePitch(theta); }
	static Matrix4 YawRotation(Float theta) { return Matrix4(true).RotateYaw(theta); }
	static Matrix4 RollRotation(Float theta) { return Matrix4(true).RotateRoll(theta); }
	static Matrix4 EulerAnglesRotation(Float pitch, Float yaw, Float roll) { return Matrix4(true).RotateEulerAngles(pitch, yaw, roll); }
	static Matrix4 EulerAnglesYawRotation(Float yaw, Float pitch, Float roll) { return Matrix4(true).RotateEulerAnglesYaw(yaw, pitch, roll); }
	static Matrix4 NewProjection(Float distance, Float nearPlane, Float farPlane, Float width, Float height) { return Matrix4(true).Projection(distance, nearPlane, farPlane, width, height); }
	static Matrix4 Facing(const Vector3& position, const Vector3& direction, const Vector3& globalUp = Vector3(0, 1, 0)) { return Matrix4(true).Face(position, direction, globalUp); }

private:
	static bool Compare(Float x, Float y, Float epsilon);

	Float Det(int y1, int y2, int x1, int x2) const;
};

constexpr Matrix4 operator*(Float scalar, const Matrix4& matrix)
{
	Matrix4 result;

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			result.Data[y][x] = scalar * matrix.Data[y][x];

	return result;
}
std::ostream& operator<<(std::ostream& out, const Matrix4& matrix);
