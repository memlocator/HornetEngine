#pragma once

import <vector>;
#include "Math/Vector3.h"
#include "Math/Matrix4.h"

struct VertexData;

class PCA
{
public:
	typedef std::vector<Vector3> VertexVector;

	Vector3 Axis1;
	Vector3 Axis2;
	Vector3 Axis3;
	Vector3 EigenValues;

	static PCA Compute(const Matrix4& covariance, int maxIterations = 50, Float epsilon = 0.0001f);
	static Matrix4 ComputeCovariance(const std::vector<VertexData>& vertices);
	static Matrix4 ComputeJacobiRotation(const Matrix4& matrix);
};