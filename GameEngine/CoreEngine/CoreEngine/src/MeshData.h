#pragma once

import <vector>;

extern "C" {
#include <glew.h>
}
#include "Math/Vector3.h"
#include "Math/Color4.h"
#include "VertexModeEnum.h"
#include "Ray.h"
#include "SceneRayCastResults.h"
#include "AabbTree.h"

class ObjParser;
class PlyParser;

struct Vector2Raw
{
	float X = 0;
	float Y = 0;

	Vector2Raw(float x = 0, float y = 0) : X(x), Y(y) {}
	Vector2Raw(double x, double y = 0) : X((float)x), Y((float)y) {}
	Vector2Raw(const Vector3& vector) : X((float)vector.X), Y((float)vector.Y) {}

	operator Vector3()
	{
		return Vector3((Float)X, (Float)Y);
	}
};

struct Vector3Raw
{
	float X = 0;
	float Y = 0;
	float Z = 0;

	Vector3Raw(float x = 0, float y = 0, float z = 0) : X(x), Y(y), Z(z) {}
	Vector3Raw(double x, double y = 0, double z = 0) : X((float)x), Y((float)y), Z((float)z) {}
	Vector3Raw(const Vector3& vector) : X((float)vector.X), Y((float)vector.Y), Z((float)vector.Z) {}

	operator Vector3() const
	{
		return Vector3((Float)X, (Float)Y, (Float)Z);
	}

	Vector3Raw operator+(const Vector3Raw& other) const
	{
		return Vector3Raw(X + other.X, Y + other.Y, Z + other.Z);
	}

	Vector3Raw operator-(const Vector3Raw& other) const
	{
		return Vector3Raw(X - other.X, Y - other.Y, Z - other.Z);
	}

	Vector3Raw operator*(Float scalar) const
	{
		return Vector3Raw(scalar * X, scalar * Y, scalar * Z);
	}
};

struct Vector4Raw
{
	float X = 0;
	float Y = 0;
	float Z = 0;
	float W = 0;

	Vector4Raw(float x = 0, float y = 0, float z = 0, float w = 0) : X(x), Y(y), Z(z), W(w) {}
	Vector4Raw(double x, double y = 0, double z = 0, double w = 0) : X((float)x), Y((float)y), Z((float)z), W((float)w) {}
	Vector4Raw(const Vector3& vector) : X((float)vector.X), Y((float)vector.Y), Z((float)vector.Z), W((float)vector.W) {}

	operator Vector3() const
	{
		return Vector3((Float)X, (Float)Y, (Float)Z, (Float)W);
	}

	Vector3Raw Unit() const
	{
		float length = std::sqrt(X * X + Y * Y + Z * Z);

		return Vector3Raw(X / length, Y / length, Z / length);
	}
};

Vector3Raw operator*(Float scalar, const Vector3Raw& vector);

struct VertexData
{
	Vector3Raw Position, Normal;
	Vector2Raw UV;
	Vector4Raw TVector, BVector;
};

struct TriangleData
{
	int VertexA = -1;
	int VertexB = -1;
	int VertexC = -1;
	int Index = -1;
};

class MeshData
{
public:
	typedef std::vector<VertexData> VertexVector;
	typedef std::vector<int> IntVector;
	typedef std::vector<TriangleData> TriangleVector;
	typedef std::function<void(const SceneRayCastResults& results)> CastResultsCallback;

	Enum::VertexMode Mode;

	VertexVector VertexBuffer;
	IntVector IndexBuffer;

	GLenum DrawMode = GL_TRIANGLES;

	MeshData(Enum::VertexMode mode = Enum::VertexMode::Seperate);
	MeshData(const ObjParser* parser, Enum::VertexMode mode = Enum::VertexMode::Seperate);
	MeshData(const PlyParser* parser, Enum::VertexMode mode = Enum::VertexMode::Seperate);
	MeshData(const MeshData* meshData, Enum::VertexMode mode = Enum::VertexMode::Seperate);
	MeshData(const MeshData& other);

	void UpdateBounds();
	void Initialize(const ObjParser* parser);
	void Initialize(const PlyParser* parser);
	void InitializeWireframe(const ObjParser* parser);
	void InitializeWireframe(const PlyParser* parser);
	void GenerateVertexNormals(const MeshData* meshData);
	void GenerateFaceNormals(const MeshData* meshData);
	void GenerateCylinderMap(const MeshData* meshData);
	void GenerateSphereMap(const MeshData* meshData);
	void GenerateCubeMap(const MeshData* meshData);
	void GenerateTBNDebug(const MeshData* meshData);
	Vector3 GetMinimumCorner() const;
	Vector3 GetMaximumCorner() const;
	Vector3 GetCenter() const;
	Vector3 GetSize() const;
	void PushTriangle(int vertexA, int vertexB, int vertexC);
	void ConfigurePartitioning();
	void CastRay(const Ray& ray, const CastResultsCallback& callback) const;
	const AabbTree& GetTree() const { return TrianglePartition; }
	int GetTriangle(const AabbTree::Node* node) const { return node->GetData<TriangleData>()->Index; }

	MeshData& operator=(const MeshData& other);

private:
	void Smoothen();

	Vector3 Minimum;
	Vector3 Maximum;

	TriangleVector Triangles;
	AabbTree TrianglePartition;
};

