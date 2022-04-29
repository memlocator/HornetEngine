#pragma once

#include <vector>
#include "Vector3.h"
#include "Matrix4.h"
#include "MeshData.h"

namespace Engine
{
	class ModelAsset;
}

struct VertexData;

class BoundingSphere
{
public:
	typedef std::vector<Vector3> VertexVector;

	Float Radius = 0;
	Vector3 Center;

	constexpr BoundingSphere(Float radius = 0, const Vector3& center = Vector3()) : Radius(radius), Center(center) {}

	bool Contains(const Vector3& point) const;
	void ExpandByPoint(const Vector3& point);

	static BoundingSphere ComputeCentroid(const std::vector<VertexData>& vertices);
	static BoundingSphere ComputeRitter(const std::vector<VertexData>& vertices);
	static BoundingSphere ComputeLarson(const std::vector<VertexData>& vertices);
	static BoundingSphere ComputePCA(const std::vector<VertexData>& vertices);
	static BoundingSphere ComputeExactSphere(const std::vector<VertexData>& vertices, int* indices, int indexCount);

	static BoundingSphere ComputeCentroid(const std::shared_ptr<Engine::ModelAsset>& model);
	static BoundingSphere ComputeRitter(const std::shared_ptr<Engine::ModelAsset>& model);
	static BoundingSphere ComputeLarson(const std::shared_ptr<Engine::ModelAsset>& model);
	static BoundingSphere ComputePCA(const std::shared_ptr<Engine::ModelAsset>& model);
};
