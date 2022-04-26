#pragma once

#include <vector>
#include "Matrix3.h"
#include "MeshData.h"

namespace Engine
{
	class ModelAsset;
}

class OBB
{
public:
	typedef std::vector<Vector3> VertexVector;

	Vector3 Size;
	Vector3 Center;
	Matrix3 Transformation;

	static OBB Compute(const MeshData::VertexVector& vertices);
	static OBB Compute(const std::shared_ptr<Engine::ModelAsset>& model);
};