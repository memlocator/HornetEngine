#pragma once

import <vector>;
#include "Matrix4.h"
import <memory>;

struct VertexData;

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
	Matrix4 Transformation;

	static OBB Compute(const std::vector<VertexData>& vertices);
	static OBB Compute(const std::shared_ptr<Engine::ModelAsset>& model);
};