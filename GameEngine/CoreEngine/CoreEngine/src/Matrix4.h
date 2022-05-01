#pragma once
/*
Matrix.Cpp
Author:
9/16/16

contains implimentation of Matrix class functions
*/

import <iostream>;
import <sstream>;

#include "Matrix4-decl.h"

extern "C" {
import <cmath>;
}


template <typename Number>
constexpr Matrix4Type<Number>::Matrix4Type()
{
	Identity();
}

template <typename Number>
constexpr Matrix4Type<Number>::Matrix4Type(bool) {}

template <typename Number>
constexpr Matrix4Type<Number>::Matrix4Type(Number x, Number y, Number z)
{
	Translate(x, y, z);
}

template <typename Number>
constexpr Matrix4Type<Number>::Matrix4Type(const Vec3& vector)
{
	Translate(vector);
}

template <typename Number>
constexpr Matrix4Type<Number>::Matrix4Type(const Vec3& position, const Vec3& right, const Vec3& up, const Vec3& front)
{
	SetVectors(position, right, up, front);
}

template <typename Number>
Matrix4Type<Number>::Matrix4Type(const Vec3& position, const Vec3& direction, const Vec3& globalUp)
{
	Face(position, direction, globalUp);
}

template <typename Number>
template <typename OtherNumber>
constexpr Matrix4Type<Number>::Matrix4Type(const Matrix3Type<OtherNumber>& mat, const Vec3& translation)
{
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			Data[x][y] = (Number)mat.Data[x][y];

	SetTranslation(translation);
}

template <typename Number>
template <typename OtherNumber>
constexpr Matrix4Type<Number>::Matrix4Type(const Matrix4Type<OtherNumber>& mat)
{
	for (int i = 0; i < 16; ++i)
		Data[i % 4][i / 4] = (Number)mat.Data[i % 4][i / 4];
}

template <typename Number>
constexpr Matrix4Type<Number>& Matrix4Type<Number>::Identity()
{
	for (int i = 0; i < 16; i++)
		Data[i % 4][i / 4] = i % 4 == i / 4;

	return *this;
}

template <typename Number>
constexpr Matrix4Type<Number>& Matrix4Type<Number>::SetVectors(const Vec3& position, const Vec3& right, const Vec3& up, const Vec3& front)
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

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::Transpose()
{
	for (int x = 1; x < 4; ++x)
	{
		for (int y = 0; y < x; ++y)
		{
			Number temp = Data[x][y];

			Data[x][y] = Data[y][x];
			Data[y][x] = temp;
		}
	}

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::SetRight(const Vec3& vector)
{
	Data[0][0] = vector.X;
	Data[1][0] = vector.Y;
	Data[2][0] = vector.Z;

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::SetUp(const Vec3& vector)
{
	Data[0][1] = vector.X;
	Data[1][1] = vector.Y;
	Data[2][1] = vector.Z;

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::SetFront(const Vec3& vector)
{
	Data[0][2] = vector.X;
	Data[1][2] = vector.Y;
	Data[2][2] = vector.Z;

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::SetTranslation(const Vec3& vector)
{
	Data[0][3] = vector.X;
	Data[1][3] = vector.Y;
	Data[2][3] = vector.Z;

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::SetTransformedTranslation(const Vec3& vector)
{
	Data[0][3] = vector.X * Data[0][0] + vector.Y * Data[0][1] + vector.Z * Data[0][2];
	Data[1][3] = vector.X * Data[1][0] + vector.Y * Data[1][1] + vector.Z * Data[1][2];
	Data[2][3] = vector.X * Data[2][0] + vector.Y * Data[2][1] + vector.Z * Data[2][2];

	return *this;
}

template <typename Number>
constexpr Matrix4Type<Number>& Matrix4Type<Number>::Translate(Number x, Number y, Number z)
{
	Identity();

	Data[0][3] = x;
	Data[1][3] = y;
	Data[2][3] = z;

	return *this;
}

template <typename Number>
constexpr Matrix4Type<Number>& Matrix4Type<Number>::Translate(const Vec3& vector)
{
	return Translate(vector.X, vector.Y, vector.Z);
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::Scale(Number x, Number y, Number z)
{
	Identity();

	Data[0][0] = x;
	Data[1][1] = y;
	Data[2][2] = z;

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::Scale(const Vec3& vector)
{
	return Scale(vector.X, vector.Y, vector.Z);
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::RotateAxis(const Vec3& vector, Number theta)
{
	Vec3 normalized = vector;

	normalized.Normalize();
	Number axis[3] = { normalized.X, normalized.Y, normalized.Z };

	Identity();

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			Data[y][x] = axis[x] * axis[y];

	Number cosine = std::cos(theta);

	*this *= 1 - cosine;

	Matrix4Type<Number> scale;

	scale.Scale(cosine, cosine, cosine);

	*this += scale;

	Matrix4Type<Number> cross(
		Vec3(),
		Vec3(0.f, -normalized.Z, normalized.Y),
		Vec3(normalized.Z, 0.f, -normalized.X),
		Vec3(-normalized.Y, normalized.X, 0.f)
	);

	cross *= std::sin(theta);

	*this += cross;

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::RotatePitch(Number theta)
{
	Identity();

	Number sine = std::sin(theta);
	Number cosine = std::cos(theta);

	Data[1][1] = cosine;
	Data[2][1] = sine;

	Data[1][2] = -sine;
	Data[2][2] = cosine;

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::RotateYaw(Number theta)
{
	Identity();

	Number sine = std::sin(theta);
	Number cosine = std::cos(theta);

	Data[0][0] = cosine;
	Data[2][0] = -sine;

	Data[0][2] = sine;
	Data[2][2] = cosine;

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::RotateRoll(Number theta)
{
	Identity();

	Number sine = std::sin(theta);
	Number cosine = std::cos(theta);

	Data[0][0] = cosine;
	Data[1][0] = sine;

	Data[0][1] = -sine;
	Data[1][1] = cosine;

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::RotateEulerAngles(Number pitch, Number yaw, Number roll)
{
	*this = Matrix4Type(true).RotateRoll(roll) * Matrix4Type(true).RotateYaw(yaw) * Matrix4Type(true).RotatePitch(pitch);

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::RotateEulerAnglesYaw(Number yaw, Number pitch, Number roll)
{
	*this = Matrix4Type(true).RotateRoll(roll) * Matrix4Type(true).RotatePitch(pitch) * Matrix4Type(true).RotateYaw(yaw);

	return *this;
}

template <typename Number>
Number Matrix4Type<Number>::Det(int y1, int y2, int x1, int x2) const
{
	return Data[y1][x1] * Data[y2][x2] - Data[y1][x2] * Data[y2][x1];
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::Inverse()
{
	Number determinant = Det();

	Number inverseData[3][3] = {};

	inverseData[0][0] = Det(1, 2, 1, 2);
	inverseData[1][0] = -Det(1, 2, 0, 2);
	inverseData[2][0] = Det(1, 2, 0, 1);

	inverseData[0][1] = -Det(0, 2, 1, 2);
	inverseData[1][1] = Det(0, 2, 0, 2);
	inverseData[2][1] = -Det(0, 2, 0, 1);

	inverseData[0][2] = Det(0, 1, 1, 2);
	inverseData[1][2] = -Det(0, 1, 0, 2);
	inverseData[2][2] = Det(0, 1, 0, 1);

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			Data[y][x] = inverseData[y][x];

	Vec3 vector = Translation();

	*this *= 1 / determinant;

	Data[0][3] = 0;
	Data[1][3] = 0;
	Data[2][3] = 0;
	Data[3][3] = 1;

	vector = *this * vector;

	Data[0][3] = -vector.X;
	Data[1][3] = -vector.Y;
	Data[2][3] = -vector.Z;

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::Invert(const Matrix4Type& other)
{
	*this = other;

	Inverse();

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::Projection(Number distance, Number near, Number far, Number width, Number height)
{
	Scale(2 * distance / width, 2 * distance / height, (near + far) / (near - far));

	Data[3][2] = -1;
	Data[2][3] = 2 * near * far / (near - far);
	Data[3][3] = 0;

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::ExtractRotation(const Matrix4Type& matrix, const Vec3& newTranslation)
{
	return SetVectors(newTranslation, matrix.RightVector().Normalize(), matrix.UpVector().Normalize(), matrix.FrontVector().Normalize());
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::TransformAround(const Vec3& point)
{
	Vec3 translationVector = (*this * -point) + point;

	Data[0][3] = translationVector.X;
	Data[1][3] = translationVector.Y;
	Data[2][3] = translationVector.Z;

	return *this;
}

template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::Face(const Vec3& position, const Vec3& direction, const Vec3& globalUp)
{
	Vec3 right = direction.Cross(globalUp).Normalize();
	Vec3 up = right.Cross(direction);

	return SetVectors(position, right, up, -direction.Unit());
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::Transposed() const
{
	return Matrix4Type(*this).Transpose();
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::Inverted() const
{
	return Matrix4Type(*this).Inverse();
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::Rotation(const Vec3& newTranslation) const
{
	return Matrix4Type(true).ExtractRotation(*this, newTranslation);
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::TransformedAround(const Vec3& point) const
{
	return Matrix4Type(*this).TransformAround(point);
}

//returns the right vector of a transformation matrix. mostly useful for rotations.
template <typename Number>
Vector3Type<Number, Number> Matrix4Type<Number>::RightVector() const
{
	return Vec3(Data[0][0], Data[1][0], Data[2][0]);
}

//returns the up vector of a transformation matrix. mostly useful for rotations.
template <typename Number>
Vector3Type<Number, Number> Matrix4Type<Number>::UpVector() const
{
	return Vec3(Data[0][1], Data[1][1], Data[2][1]);
}

//returns the front vector of a transformation matrix. mostly useful for rotations.
template <typename Number>
Vector3Type<Number, Number> Matrix4Type<Number>::FrontVector() const
{
	return Vec3(Data[0][2], Data[1][2], Data[2][2]);
}

// returns the translation of the transformation matrix as a point
template <typename Number>
Vector3Type<Number, Number> Matrix4Type<Number>::Translation() const
{
	return Vec3(Data[0][3], Data[1][3], Data[2][3], 1.f);
}

template <typename Number>
Vector3Type<Number, Number> Matrix4Type<Number>::ExtractScale() const
{
	return Vec3(RightVector().Length(), UpVector().Length(), FrontVector().Length());
}

template <typename Number>
Number Matrix4Type<Number>::Det() const
{
	return Data[0][0] * Det(1, 2, 1, 2) - Data[0][1] * Det(1, 2, 0, 2) + Data[0][2] * Det(1, 2, 0, 1);
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::operator+(const Matrix4Type& other) const
{
	Matrix4Type<Number> result;

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			result.Data[y][x] = Data[y][x] + other.Data[y][x];

	return result;
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::operator-(const Matrix4Type& other) const
{
	Matrix4Type result;

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			result.Data[y][x] = Data[y][x] - other.Data[y][x];

	return result;
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::operator-() const
{
	Matrix4Type result;

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			result.Data[y][x] = -Data[y][x];

	return result;
}

// scalar multiply
template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::operator*(Number scalar) const
{
	Matrix4Type result;

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			result.Data[y][x] = scalar * Data[y][x];

	return result;
}

//overloaded multiplication operator
template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::operator*(const Matrix4Type<Number>& other) const
{
	Matrix4Type results;

	results.Data[0][0] = 0;
	results.Data[1][1] = 0;
	results.Data[2][2] = 0;
	results.Data[3][3] = 0;
	//results.Data[3][3] = Data[3][3] * other.Data[3][3];

	//for (int x = 0; x < 3; ++x)
	//	for (int y = 0; y < 4; ++y)
	//		for (int i = 0; i < 3; ++i)
	//			results.Data[x][y] += Data[x][i] * other.Data[i][y];
	//
	//for (int i = 0; i < 3; ++i)
	//	results.Data[i][3] += Data[i][3];


	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			for (int i = 0; i < 4; ++i)
				results.Data[x][y] += Data[x][i] * other.Data[i][y];

	return results;
}

// transform a vector
template <typename Number>
Vector3Type<Number, Number> Matrix4Type<Number>::operator*(const Vec3& other) const
{
	return Vec3(
		other.X * Data[0][0] + other.Y * Data[0][1] + other.Z * Data[0][2] + other.W * Data[0][3],
		other.X * Data[1][0] + other.Y * Data[1][1] + other.Z * Data[1][2] + other.W * Data[1][3],
		other.X * Data[2][0] + other.Y * Data[2][1] + other.Z * Data[2][2] + other.W * Data[2][3],
		other.X * Data[3][0] + other.Y * Data[3][1] + other.Z * Data[3][2] + other.W * Data[3][3]
	);
}

template <typename Number>
Number* Matrix4Type<Number>::operator[](int row)
{
	return Data[row];
}

template <typename Number>
const Number* Matrix4Type<Number>::operator[](int row) const
{
	return Data[row];
}

// assignment
template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::operator=(const Matrix4Type& other)
{
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			Data[y][x] = other.Data[y][x];

	return *this;
}

// addition assignment
template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::operator+=(const Matrix4Type& other)
{
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			Data[y][x] += other.Data[y][x];

	return *this;
}

// subtraction assignment
template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::operator-=(const Matrix4Type& other)
{
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			Data[y][x] -= other.Data[y][x];

	return *this;
}

// transformation assignment
template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::operator*=(const Matrix4Type& other)
{
	*this = *this * other;

	return *this;
}

// scalar assignment
template <typename Number>
Matrix4Type<Number>& Matrix4Type<Number>::operator*=(Number scalar)
{
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			Data[y][x] *= scalar;

	return *this;
}

template <typename Number>
bool Matrix4Type<Number>::Compare(Number x, Number y, Number epsilon)
{
	return std::abs(x - y) < epsilon;
}

template <typename Number>
bool Matrix4Type<Number>::operator==(const Matrix4Type& other) const
{
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (!Compare(Data[y][x], other.Data[y][x], 1e-4f))
				return false;

	return true;
}

template <typename Number>
bool Matrix4Type<Number>::operator!=(const Matrix4Type& other) const
{
	return !(*this == other);
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::NewScale(Number x, Number y, Number z)
{
	return Matrix4Type(true).Scale(x, y, z);
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::NewScale(const Vec3& vector)
{
	return Matrix4Type(true).Scale(vector);
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::AxisRotation(const Vec3& axis, Number theta)
{
	return Matrix4Type(true).RotateAxis(axis, theta);
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::PitchRotation(Number theta)
{
	return Matrix4Type(true).RotatePitch(theta);
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::YawRotation(Number theta)
{
	return Matrix4Type(true).RotateYaw(theta);
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::RollRotation(Number theta)
{
	return Matrix4Type(true).RotateRoll(theta);
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::EulerAnglesRotation(Number pitch, Number yaw, Number roll)
{
	return Matrix4Type(true).RotateEulerAngles(pitch, yaw, roll);
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::EulerAnglesYawRotation(Number yaw, Number pitch, Number roll)
{
	return Matrix4Type(true).RotateEulerAnglesYaw(yaw, pitch, roll);
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::NewProjection(Number distance, Number nearPlane, Number farPlane, Number width, Number height)
{
	return Matrix4Type(true).Projection(distance, nearPlane, farPlane, width, height);
}

template <typename Number>
Matrix4Type<Number> Matrix4Type<Number>::Facing(const Vec3& position, const Vec3& direction, const Vec3& globalUp)
{
	return Matrix4Type(true).Face(position, direction, globalUp);
}

template <typename Number>
Matrix4Type<Number>::operator std::string() const
{
	std::stringstream out;

	out << *this;

	return out.str();
}

// stream output
template <typename Number>
std::ostream& operator<<(std::ostream& out, const Matrix4Type<Number>& matrix)
{
	// put the formatted data into the provided output stream
	out << "[ " << matrix.Data[0][0] << ", " << matrix.Data[0][1] << ", " << matrix.Data[0][2] << ", " << matrix.Data[0][3] << " ]\n"
		<< "[ " << matrix.Data[1][0] << ", " << matrix.Data[1][1] << ", " << matrix.Data[1][2] << ", " << matrix.Data[1][3] << " ]\n"
		<< "[ " << matrix.Data[2][0] << ", " << matrix.Data[2][1] << ", " << matrix.Data[2][2] << ", " << matrix.Data[2][3] << " ]\n"
		<< "[ " << matrix.Data[3][0] << ", " << matrix.Data[3][1] << ", " << matrix.Data[3][2] << ", " << matrix.Data[3][3] << " ]" << std::endl;

	return out;
}
