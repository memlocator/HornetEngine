#include "PCA.h"

#include "MeshData.h"

PCA PCA::Compute(const Matrix4& covariance, int maxIterations, Float epsilon)
{
	Matrix4 eigenVectors;
	Matrix4 diagonal = covariance;

	for (int i = 0; i < maxIterations; ++i)
	{
		Matrix4 rotation = ComputeJacobiRotation(diagonal);

		eigenVectors = eigenVectors * rotation;
		diagonal = diagonal * rotation;

		rotation.Data[0][1] *= -1;
		rotation.Data[0][2] *= -1;
		rotation.Data[1][2] *= -1;

		rotation.Data[1][0] *= -1;
		rotation.Data[2][0] *= -1;
		rotation.Data[2][1] *= -1;

		diagonal = rotation * diagonal;

		if (diagonal.Data[0][1] * diagonal.Data[0][1] + diagonal.Data[0][2] * diagonal.Data[0][2] + diagonal.Data[1][2] * diagonal.Data[1][2] +
			diagonal.Data[1][0] * diagonal.Data[1][0] + diagonal.Data[2][0] * diagonal.Data[2][0] + diagonal.Data[2][1] * diagonal.Data[2][1] < epsilon)
			break;
	}

	PCA results;

	results.Axis1 = eigenVectors.RightVector();
	results.Axis2 = eigenVectors.UpVector();
	results.Axis3 = eigenVectors.FrontVector();
	results.EigenValues.Set(diagonal.Data[0][0], diagonal.Data[1][1], diagonal.Data[2][2]);

	return results;
}

Matrix4 PCA::ComputeCovariance(const MeshData::VertexVector& vertices)
{
	Vector3 mean(0, 0, 0);

	for (int i = 0; i < int(vertices.size()); ++i)
		mean += vertices[i].Position;

	mean *= 1 / Float(vertices.size());

	Matrix4 covariance;

	covariance.Data[0][0] = 0;
	covariance.Data[1][1] = 0;
	covariance.Data[2][2] = 0;

	for (int i = 0; i < int(vertices.size()); ++i)
	{
		Vector3 vec = vertices[i].Position - mean;

		for (int j = 0; j < 9; ++j)
			covariance.Data[j / 3][j % 3] += vec[j / 3] * vec[j % 3];
	}

	for (int i = 0; i < 9; ++i)
		covariance.Data[i / 3][i % 3] /= Float(vertices.size());

	return covariance;
}

namespace
{
	struct SinCos
	{
		Float s, c;
	};

	SinCos computeRotation(Float diag1, Float diag2, Float offDiag)
	{
		SinCos values;

		Float b = 0.5f * (diag2 - diag1) / offDiag;

		Float tangent = (b >= 0 ? 1 : -1) / (std::abs(b) + std::sqrt(b * b + 1));

		values.c = std::sqrt(1 / (tangent * tangent + 1));
		values.s = std::sqrt(1 - values.c * values.c);

		if (tangent < 0)
			values.s *= -1;

		return values;
	}
}

Matrix4 PCA::ComputeJacobiRotation(const Matrix4& matrix)
{
	Float val1 = abs(matrix.Data[0][1]);
	Float val2 = abs(matrix.Data[0][2]);
	Float val3 = abs(matrix.Data[1][2]);

	Matrix4 rotation;

	if (val1 > val2&& val1 > val3)
	{
		SinCos values = computeRotation(matrix.Data[0][0], matrix.Data[1][1], matrix.Data[0][1]);

		rotation.Data[0][0] = values.c;
		rotation.Data[1][1] = values.c;
		rotation.Data[0][1] = values.s;
		rotation.Data[1][0] = -values.s;
	}
	else if (val2 > val1&& val2 > val3)
	{
		SinCos values = computeRotation(matrix.Data[0][0], matrix.Data[2][2], matrix.Data[0][2]);

		rotation.Data[0][0] = values.c;
		rotation.Data[2][2] = values.c;
		rotation.Data[0][2] = values.s;
		rotation.Data[2][0] = -values.s;
	}
	else
	{
		SinCos values = computeRotation(matrix.Data[1][1], matrix.Data[2][2], matrix.Data[1][2]);

		rotation.Data[1][1] = values.c;
		rotation.Data[2][2] = values.c;
		rotation.Data[1][2] = values.s;
		rotation.Data[2][1] = -values.s;
	}

	return rotation;
}