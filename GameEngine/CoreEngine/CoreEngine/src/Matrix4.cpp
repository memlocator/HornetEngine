/*
Matrix.Cpp
Author: 
9/16/16

contains implimentation of Matrix class functions
*/

#include <iostream>
#include <sstream>

#include "Matrix4.h"

extern "C" {
#include <math.h>
}


Matrix4::Matrix4(const Vector3& position, const Vector3& direction, const Vector3& globalUp)
{
	Face(position, direction, globalUp);
}

Matrix4& Matrix4::Transpose()
{
	for (int x = 1; x < 4; ++x)
	{
		for (int y = 0; y < x; ++y)
		{
			Float temp = Data[x][y];

			Data[x][y] = Data[y][x];
			Data[y][x] = temp;
		}
	}

	return *this;
}

Matrix4& Matrix4::SetRight(const Vector3& vector)
{
	Data[0][0] = vector.X;
	Data[1][0] = vector.Y;
	Data[2][0] = vector.Z;

	return *this;
}

Matrix4& Matrix4::SetUp(const Vector3& vector)
{
	Data[0][1] = vector.X;
	Data[1][1] = vector.Y;
	Data[2][1] = vector.Z;

	return *this;
}

Matrix4& Matrix4::SetFront(const Vector3& vector)
{
	Data[0][2] = vector.X;
	Data[1][2] = vector.Y;
	Data[2][2] = vector.Z;

	return *this;
}

Matrix4& Matrix4::SetTranslation(const Vector3& vector)
{
	Data[0][3] = vector.X;
	Data[1][3] = vector.Y;
	Data[2][3] = vector.Z;

	return *this;
}

Matrix4& Matrix4::SetTransformedTranslation(const Vector3& vector)
{
	Data[0][3] = vector.X * Data[0][0] + vector.Y * Data[0][1] + vector.Z * Data[0][2];
	Data[1][3] = vector.X * Data[1][0] + vector.Y * Data[1][1] + vector.Z * Data[1][2];
	Data[2][3] = vector.X * Data[2][0] + vector.Y * Data[2][1] + vector.Z * Data[2][2];

	return *this;
}

Matrix4& Matrix4::Scale(Float x, Float y, Float z)
{
	Identity();

	Data[0][0] = x;
	Data[1][1] = y;
	Data[2][2] = z;

	return *this;
}

Matrix4& Matrix4::Scale(const Vector3& vector)
{
	return Scale(vector.X, vector.Y, vector.Z);
}

Matrix4& Matrix4::RotateAxis(const Vector3& vector, Float theta)
{
	Vector3 normalized = vector;

	normalized.Normalize();
	Float axis[3] = { normalized.X, normalized.Y, normalized.Z };

	Identity();

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			Data[y][x] = axis[x] * axis[y];

	Float cosine = std::cos(theta);

	*this *= 1 - cosine;

	Matrix4 scale;

	scale.Scale(cosine, cosine, cosine);

	*this += scale;

	Matrix4 cross(
		Vector3(),
		Vector3(0._F, -normalized.Z, normalized.Y),
		Vector3(normalized.Z, 0._F, -normalized.X),
		Vector3(-normalized.Y, normalized.X, 0._F)
	);

	cross *= std::sin(theta);

	*this += cross;

	return *this;
}

Matrix4& Matrix4::RotatePitch(Float theta)
{
	Identity();

	Float sine = std::sin(theta);
	Float cosine = std::cos(theta);

	Data[1][1] = cosine;
	Data[2][1] = sine;

	Data[1][2] = -sine;
	Data[2][2] = cosine;

	return *this;
}

Matrix4& Matrix4::RotateYaw(Float theta)
{
	Identity();

	Float sine = std::sin(theta);
	Float cosine = std::cos(theta);

	Data[0][0] = cosine;
	Data[2][0] = -sine;

	Data[0][2] = sine;
	Data[2][2] = cosine;

	return *this;
}

Matrix4& Matrix4::RotateRoll(Float theta)
{
	Identity();

	Float sine = std::sin(theta);
	Float cosine = std::cos(theta);

	Data[0][0] = cosine;
	Data[1][0] = sine;

	Data[0][1] = -sine;
	Data[1][1] = cosine;

	return *this;
}

Matrix4& Matrix4::RotateEulerAngles(Float pitch, Float yaw, Float roll)
{
	*this = Matrix4(true).RotateRoll(roll) * Matrix4(true).RotateYaw(yaw) * Matrix4(true).RotatePitch(pitch);

	return *this;
}

Matrix4& Matrix4::RotateEulerAnglesYaw(Float yaw, Float pitch, Float roll)
{
	*this = Matrix4(true).RotateRoll(roll) * Matrix4(true).RotatePitch(pitch) * Matrix4(true).RotateYaw(yaw);

	return *this;
}

Float Matrix4::Det(int y1, int y2, int x1, int x2) const
{
	return Data[y1][x1] * Data[y2][x2] - Data[y1][x2] * Data[y2][x1];
}

Matrix4& Matrix4::Inverse()
{
	Float determinant = Det();

	Float inverseData[3][3] = {};

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

	Vector3 vector = Translation();

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

Matrix4& Matrix4::Invert(const Matrix4& other)
{
	*this = other;

	Inverse();

	return *this;
}

Matrix4& Matrix4::Projection(Float distance, Float near, Float far, Float width, Float height)
{
	Scale(2 * distance / width, 2 * distance / height, (near + far) / (near - far));

	Data[3][2] = -1;
	Data[2][3] = 2 * near * far / (near - far);
	Data[3][3] = 0;

	return *this;
}

Matrix4& Matrix4::ExtractRotation(const Matrix4& matrix, const Vector3& newTranslation)
{
	return SetVectors(newTranslation, matrix.RightVector().Normalize(), matrix.UpVector().Normalize(), matrix.FrontVector().Normalize());
}

Matrix4& Matrix4::TransformAround(const Vector3& point)
{
	Vector3 translationVector = (*this * -point) + point;

	Data[0][3] = translationVector.X;
	Data[1][3] = translationVector.Y;
	Data[2][3] = translationVector.Z;

	return *this;
}

Matrix4& Matrix4::Face(const Vector3& position, const Vector3& direction, const Vector3& globalUp)
{
	Vector3 right = direction.Cross(globalUp).Normalize();
	Vector3 up = right.Cross(direction);

	return SetVectors(position, right, up, -direction.Unit());
}

//returns the right vector of a transformation matrix. mostly useful for rotations.
Vector3 Matrix4::RightVector() const
{
	return Vector3(Data[0][0], Data[1][0], Data[2][0]);
}

//returns the up vector of a transformation matrix. mostly useful for rotations.
Vector3 Matrix4::UpVector() const
{
	return Vector3(Data[0][1], Data[1][1], Data[2][1]);
}

//returns the front vector of a transformation matrix. mostly useful for rotations.
Vector3 Matrix4::FrontVector() const
{
	return Vector3(Data[0][2], Data[1][2], Data[2][2]);
}

// returns the translation of the transformation matrix as a point
Vector3 Matrix4::Translation() const
{
	return Vector3(Data[0][3], Data[1][3], Data[2][3], 1._F);
}

Vector3 Matrix4::ExtractScale() const
{
	return Vector3(RightVector().Length(), UpVector().Length(), FrontVector().Length());
}

Float Matrix4::Det() const
{
	return Data[0][0] * Det(1, 2, 1, 2) - Data[0][1] * Det(1, 2, 0, 2) + Data[0][2] * Det(1, 2, 0, 1);
}

Matrix4 Matrix4::operator+(const Matrix4& other) const
{
	Matrix4 result;

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			result.Data[y][x] = Data[y][x] + other.Data[y][x];

	return result;
}

Matrix4 Matrix4::operator-(const Matrix4& other) const
{
	Matrix4 result;

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			result.Data[y][x] = Data[y][x] - other.Data[y][x];

	return result;
}

Matrix4 Matrix4::operator-() const
{
	Matrix4 result;

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			result.Data[y][x] = -Data[y][x];

	return result;
}

// scalar multiply
Matrix4 Matrix4::operator*(Float scalar) const
{
	Matrix4 result;

	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			result.Data[y][x] = scalar * Data[y][x];

	return result;
}

//overloaded multiplication operator
Matrix4 Matrix4::operator*(const Matrix4& other) const
{
	Matrix4 results;

	results.Data[0][0] = 0;
	results.Data[1][1] = 0;
	results.Data[2][2] = 0;
	results.Data[3][3] = 0;
	//results.Data[3][3] = Data[3][3] * other.Data[3][3];

	//if (Data[3][0] != 0 || Data[3][1] != 0 || Data[3][2] != 0)
	//	results[3][3] = 1;
	//
	//if (other.Data[3][0] != 0 || other.Data[3][1] != 0 || other.Data[3][2] != 0)
	//	results[3][3] = 1;

	//results.Data[0][0] = ComponentMultiplicationNoAffine(other, 0, 0);
	//results.Data[0][1] = ComponentMultiplicationNoAffine(other, 0, 1);
	//results.Data[0][2] = ComponentMultiplicationNoAffine(other, 0, 2);
	//results.Data[0][3] = ComponentMultiplicationNoAffine(other, 0, 3) + Data[0][3];
	//
	//// multiply second row
	//results.Data[1][0] = ComponentMultiplicationNoAffine(other, 1, 0);
	//results.Data[1][1] = ComponentMultiplicationNoAffine(other, 1, 1);
	//results.Data[1][2] = ComponentMultiplicationNoAffine(other, 1, 2);
	//results.Data[1][3] = ComponentMultiplicationNoAffine(other, 1, 3) + Data[1][3];
	//
	//// multiply third row
	//results.Data[2][0] = ComponentMultiplicationNoAffine(other, 2, 0);
	//results.Data[2][1] = ComponentMultiplicationNoAffine(other, 2, 1);
	//results.Data[2][2] = ComponentMultiplicationNoAffine(other, 2, 2);
	//results.Data[2][3] = ComponentMultiplicationNoAffine(other, 2, 3) + Data[2][3];

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
Vector3 Matrix4::operator*(const Vector3& other) const
{
	return Vector3(
		other.X * Data[0][0] + other.Y * Data[0][1] + other.Z * Data[0][2] + other.W * Data[0][3],
		other.X * Data[1][0] + other.Y * Data[1][1] + other.Z * Data[1][2] + other.W * Data[1][3],
		other.X * Data[2][0] + other.Y * Data[2][1] + other.Z * Data[2][2] + other.W * Data[2][3],
		other.X * Data[3][0] + other.Y * Data[3][1] + other.Z * Data[3][2] + other.W * Data[3][3]
	);
}

Float* Matrix4::operator[](int row)
{
	return Data[row];
}

const Float* Matrix4::operator[](int row) const
{
	return Data[row];
}

// assignment
Matrix4& Matrix4::operator=(const Matrix4& other)
{
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			Data[y][x] = other.Data[y][x];

	return *this;
}

// addition assignment
Matrix4& Matrix4::operator+=(const Matrix4& other)
{
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			Data[y][x] += other.Data[y][x];

	return *this;
}

// subtraction assignment
Matrix4& Matrix4::operator-=(const Matrix4& other)
{
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			Data[y][x] -= other.Data[y][x];

	return *this;
}

// transformation assignment
Matrix4& Matrix4::operator*=(const Matrix4& other)
{
	*this = *this * other;

	return *this;
}

// scalar assignment
Matrix4& Matrix4::operator*=(Float scalar)
{
	for (int x = 0; x < 3; ++x)
		for (int y = 0; y < 3; ++y)
			Data[y][x] *= scalar;

	return *this;
}

bool Matrix4::Compare(Float x, Float y, Float epsilon)
{
	return std::abs(x - y) < epsilon;
}

bool Matrix4::operator==(const Matrix4& other) const
{
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
			if (!Compare(Data[y][x], other.Data[y][x], 1e-4f))
				return false;

	return true;
}

bool Matrix4::operator!=(const Matrix4& other) const
{
	return !(*this == other);
}

Matrix4::operator std::string() const
{
	std::stringstream out;

	out << *this;

	return out.str();
}
	
// stream output
std::ostream& operator<<(std::ostream &out, const Matrix4 &matrix)
{
	// put the formatted data into the provided output stream
	out << "[ " << matrix.Data[0][0] << ", " << matrix.Data[0][1] << ", " << matrix.Data[0][2] << ", " << matrix.Data[0][3] << " ]\n"
		<< "[ " << matrix.Data[1][0] << ", " << matrix.Data[1][1] << ", " << matrix.Data[1][2] << ", " << matrix.Data[1][3] << " ]\n"
		<< "[ " << matrix.Data[2][0] << ", " << matrix.Data[2][1] << ", " << matrix.Data[2][2] << ", " << matrix.Data[2][3] << " ]\n"
		<< "[ " << matrix.Data[3][0] << ", " << matrix.Data[3][1] << ", " << matrix.Data[3][2] << ", " << matrix.Data[3][3] << " ]" << std::endl;
		
	return out;
}
