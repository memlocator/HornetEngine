#include "MeshData.h"

import <map>;
extern "C" {
import <cmath>;
}

import <algorithm>;

#include "Constants.h"
#include "ObjParser.h"
#include "PlyParser.h"

Vector3Raw operator*(Float scalar, const Vector3Raw& vector)
{
	return vector * scalar;
}

MeshData::MeshData(Enum::VertexMode mode) : Mode(mode)
{

	if (mode == Enum::VertexMode::Wireframe)
		DrawMode = GL_LINES;
}

MeshData::MeshData(const ObjParser* parser, Enum::VertexMode mode) : Mode(mode)
{
	if (mode != Enum::VertexMode::Wireframe)
		Initialize(parser);
	else
		InitializeWireframe(parser);

	if (mode == Enum::VertexMode::Wireframe)
		DrawMode = GL_LINES;
}

MeshData::MeshData(const PlyParser* parser, Enum::VertexMode mode) : Mode(mode)
{
	if (mode != Enum::VertexMode::Wireframe)
		Initialize(parser);
	else
		InitializeWireframe(parser);

	if (mode == Enum::VertexMode::Wireframe)
		DrawMode = GL_LINES;
}

MeshData::MeshData(const MeshData* meshData, Enum::VertexMode mode) : Mode(mode), VertexBuffer(meshData->VertexBuffer), IndexBuffer(meshData->IndexBuffer), Minimum(meshData->Minimum), Maximum(meshData->Maximum)
{
	if (mode == Enum::VertexMode::Smoothened)
		Smoothen();

	if (mode == Enum::VertexMode::Wireframe)
		DrawMode = GL_LINES;
}

MeshData::MeshData(const MeshData& other)
{
	*this = other;
}

namespace
{
	typedef std::map<std::string, int> IndexMap;

	void compareMin(Float& x, float& y)
	{
		if (y < x)
			x = (Float)y;
	}

	void compareMax(Float& x, float& y)
	{
		if (y > x)
			x = (Float)y;
	}

	void compareVector(Vector3& minimum, Vector3& maximum, Vector3Raw& vector)
	{
		compareMin(minimum.X, vector.X);
		compareMin(minimum.Y, vector.Y);
		compareMin(minimum.Z, vector.Z);

		compareMax(maximum.X, vector.X);
		compareMax(maximum.Y, vector.Y);
		compareMax(maximum.Z, vector.Z);
	}
}

void MeshData::Initialize(const ObjParser* parser)
{
	IndexMap vertexReferences;

	for (int i = 0; i < int(parser->Faces.size()); ++i)
	{
		const Face& face = parser->Faces[i];

		Vector3 A = parser->Vertices[face.Vertices[0].Position];
		Vector3 B = parser->Vertices[face.Vertices[1].Position];
		Vector3 C = parser->Vertices[face.Vertices[2].Position];

		Vector3 uvA = parser->UVs[face.Vertices[0].UV];
		Vector3 uvB = parser->UVs[face.Vertices[1].UV];
		Vector3 uvC = parser->UVs[face.Vertices[2].UV];

		Vector3 P = B - A;
		Vector3 Q = C - A;

		Vector3 uvP = uvB - uvA;
		Vector3 uvQ = uvC - uvA;

		Float denominator = 1.0f / (uvP.X * uvQ.Y - uvP.Y * uvQ.X);

		Vector3 tVector = denominator * (P * uvQ.Y - Q * uvP.Y);
		Vector3 bVector = denominator * (Q * uvP.X - P * uvQ.X);

		for (int j = 0; j < 3; ++j)
		{
			const Vertex& indices = face.Vertices[j];
			const std::string& data = face.Data[j];

			IndexMap::iterator reference;
			
			if (Mode != Enum::VertexMode::Seperate)
				reference = vertexReferences.find(data);

			int index;

			if (Mode != Enum::VertexMode::Seperate && reference != vertexReferences.end())
				index = reference->second;
			else
			{
				index = int(VertexBuffer.size());

				VertexData vertex;

				vertex.Position = parser->Vertices[indices.Position];
				vertex.Normal = parser->Normals[indices.Normal];
				vertex.UV = parser->UVs[indices.UV];
				vertex.TVector = tVector;
				vertex.BVector = bVector;

				compareVector(Minimum, Maximum, vertex.Position);

				if (Mode != Enum::VertexMode::Seperate)
					vertexReferences[data] = index;

				VertexBuffer.push_back(vertex);
			}

			IndexBuffer.push_back(index);
		}

		Triangles.push_back(TriangleData { IndexBuffer[IndexBuffer.size() - 3], IndexBuffer[IndexBuffer.size() - 2], IndexBuffer[IndexBuffer.size() - 1], int(Triangles.size()) });
	}

	Minimum.W = 1;
	Maximum.W = 1;

	ConfigurePartitioning();
}

void MeshData::InitializeWireframe(const ObjParser* parser)
{

	for (int i = 0; i < int(parser->Faces.size()); ++i)
	{
		const Face& face = parser->Faces[i];

		Vector3 A = parser->Vertices[face.Vertices[0].Position];
		Vector3 B = parser->Vertices[face.Vertices[1].Position];
		Vector3 C = parser->Vertices[face.Vertices[2].Position];

		int index = int(VertexBuffer.size());

		VertexData vertex1;

		vertex1.Position = A;

		VertexData vertex2;

		vertex2.Position = B;

		VertexData vertex3;

		vertex3.Position = C;

		VertexBuffer.push_back(vertex1);
		VertexBuffer.push_back(vertex2);
		VertexBuffer.push_back(vertex3);

		compareVector(Minimum, Maximum, vertex1.Position);
		compareVector(Minimum, Maximum, vertex2.Position);
		compareVector(Minimum, Maximum, vertex3.Position);

		IndexBuffer.push_back(index);
		IndexBuffer.push_back(index + 1);
		IndexBuffer.push_back(index + 1);
		IndexBuffer.push_back(index + 2);
		IndexBuffer.push_back(index + 2);
		IndexBuffer.push_back(index);
	}

	Minimum.W = 1;
	Maximum.W = 1;
}

void MeshData::UpdateBounds()
{
	Minimum = Vector3(0, 0, 0, 1);
	Maximum = Vector3(0, 0, 0, 1);

	if (VertexBuffer.size() != 0)
	{
		Minimum = VertexBuffer[1].Position;
		Maximum = VertexBuffer[1].Position;
	}

	for (int i = 1; i < int(VertexBuffer.size()); ++i)
	{
		Minimum.X = std::min(Minimum.X, VertexBuffer[i].Position.X);
		Minimum.Y = std::min(Minimum.Y, VertexBuffer[i].Position.Y);
		Minimum.Z = std::min(Minimum.Z, VertexBuffer[i].Position.Z);

		Maximum.X = std::max(Maximum.X, VertexBuffer[i].Position.X);
		Maximum.Y = std::max(Maximum.Y, VertexBuffer[i].Position.Y);
		Maximum.Z = std::max(Maximum.Z, VertexBuffer[i].Position.Z);
	}
}

void MeshData::Initialize(const PlyParser* parser)
{
	int index = 0;

	for (int i = 0; i < int(parser->MeshData.size()); ++i)
	{
		auto& elementData = parser->MeshData[i];
		auto& element = elementData.Element;

		if (element->Name == "vertex")
		{
			VertexData vertex;

			for (int j = 0; j < int(elementData.Data.size()); ++j)
			{
				auto& data = elementData.Data[j];
				auto& property = data.Property;

				if (property->Name == "x")
					vertex.Position.X = data.get<float>();
				else if (property->Name == "y")
					vertex.Position.Y = data.get<float>();
				else if (property->Name == "z")
					vertex.Position.Z = data.get<float>();
				else if (property->Name == "nx")
					vertex.Normal.X = data.get<float>();
				else if (property->Name == "ny")
					vertex.Normal.Y = data.get<float>();
				else if (property->Name == "nz")
					vertex.Normal.Z = data.get<float>();
			}

			compareVector(Minimum, Maximum, vertex.Position);

			VertexBuffer.push_back(vertex);
		}
		else if (element->Name == "face")
		{
			for (int j = 0; j < int(elementData.Data.size()); ++j)
			{
				auto& data = elementData.Data[j];
				auto& property = data.Property;

				if (property->Name == "vertex_indices")
				{
					IndexBuffer.push_back(data.get<int>(0));
					IndexBuffer.push_back(data.get<int>(1));
					IndexBuffer.push_back(data.get<int>(2));

					Triangles.push_back(TriangleData { IndexBuffer[IndexBuffer.size() - 3], IndexBuffer[IndexBuffer.size() - 2], IndexBuffer[IndexBuffer.size() - 1], int(Triangles.size()) });
				}
			}
		}
	}

	Minimum.W = 1;
	Maximum.W = 1;

	ConfigurePartitioning();
}

void MeshData::InitializeWireframe(const PlyParser* parser)
{

}

void MeshData::GenerateVertexNormals(const MeshData* meshData)
{
	for (int i = 0; i < int(meshData->VertexBuffer.size()); ++i)
	{
		const VertexData& meshVertex = meshData->VertexBuffer[i];

		VertexData vertex1;

		vertex1.Position = meshVertex.Position;
		vertex1.Normal = meshVertex.Normal;

		IndexBuffer.push_back(int(VertexBuffer.size()));
		VertexBuffer.push_back(vertex1);

		VertexData vertex2;

		vertex2.Position = meshVertex.Position + 0.25_F * vertex1.Normal;
		vertex2.Normal = meshVertex.Normal;

		IndexBuffer.push_back(int(VertexBuffer.size()));
		VertexBuffer.push_back(vertex2);

		compareVector(Minimum, Maximum, vertex1.Position);
		compareVector(Minimum, Maximum, vertex2.Position);
	}
}

void MeshData::GenerateFaceNormals(const MeshData* meshData)
{
	for (int i = 0; i < int(meshData->VertexBuffer.size()); i += 3)
	{
		Vector3Raw point1 = meshData->VertexBuffer[i + 0].Position;
		Vector3Raw point2 = meshData->VertexBuffer[i + 1].Position;
		Vector3Raw point3 = meshData->VertexBuffer[i + 2].Position;

		Vector3 point = (1._F / 3._F) * point1 + (1.0_F / 3) * point2 + (1.0_F / 3) * point3;
		Vector3Raw normal = meshData->VertexBuffer[i].Normal;

		VertexData vertex1;

		vertex1.Position = point;
		vertex1.Normal = normal;

		IndexBuffer.push_back(int(VertexBuffer.size()));
		VertexBuffer.push_back(vertex1);

		VertexData vertex2;

		vertex2.Position = point + 0.25_F * normal;
		vertex2.Normal = normal;

		IndexBuffer.push_back(int(VertexBuffer.size()));
		VertexBuffer.push_back(vertex2);

		compareVector(Minimum, Maximum, vertex1.Position);
		compareVector(Minimum, Maximum, vertex2.Position);
	}
}

void MeshData::GenerateTBNDebug(const MeshData* meshData)
{
	for (int i = 0; i < int(meshData->VertexBuffer.size()); ++i)
	{
		const VertexData& meshVertex = meshData->VertexBuffer[i];

		VertexData vertex1;

		vertex1.Position = meshVertex.Position;
		vertex1.Normal = meshVertex.Normal;

		IndexBuffer.push_back(int(VertexBuffer.size()));
		VertexBuffer.push_back(vertex1);

		VertexData vertex2;

		vertex2.Position = meshVertex.Position + 0.125f * meshData->GetSize().Y * vertex1.Normal;
		vertex2.Normal = meshVertex.Normal;

		IndexBuffer.push_back(int(VertexBuffer.size()));
		VertexBuffer.push_back(vertex2);

		VertexData vertex3 = vertex1;

		IndexBuffer.push_back(int(VertexBuffer.size()));
		VertexBuffer.push_back(vertex3);

		VertexData vertex4;

		vertex4.Position = meshVertex.Position + 0.125f * meshData->GetSize().Y * meshVertex.BVector.Unit();
		vertex4.Normal = meshVertex.Normal;

		IndexBuffer.push_back(int(VertexBuffer.size()));
		VertexBuffer.push_back(vertex4);

		VertexData vertex5 = vertex1;

		IndexBuffer.push_back(int(VertexBuffer.size()));
		VertexBuffer.push_back(vertex5);

		VertexData vertex6;

		vertex6.Position = meshVertex.Position + 0.125f * meshData->GetSize().Y * meshVertex.TVector.Unit();
		vertex6.Normal = meshVertex.Normal;

		IndexBuffer.push_back(int(VertexBuffer.size()));
		VertexBuffer.push_back(vertex6);

		compareVector(Minimum, Maximum, vertex1.Position);
	}
}

void MeshData::PushTriangle(int vertexA, int vertexB, int vertexC)
{
	Triangles.push_back(TriangleData { vertexA, vertexB, vertexC, int(Triangles.size()) });
}

void MeshData::ConfigurePartitioning()
{
	for (int i = 0; i < int(Triangles.size()); ++i)
	{
		const Vector3Raw& vertexA = VertexBuffer[Triangles[i].VertexA].Position;
		const Vector3Raw& vertexB = VertexBuffer[Triangles[i].VertexB].Position;
		const Vector3Raw& vertexC = VertexBuffer[Triangles[i].VertexC].Position;
		
		Aabb triangleBox(
			Vector3(
				std::min(std::min(vertexA.X, vertexB.X), vertexC.X) - 0.01_F,
				std::min(std::min(vertexA.Y, vertexB.Y), vertexC.Y) - 0.01_F,
				std::min(std::min(vertexA.Z, vertexB.Z), vertexC.Z) - 0.01_F,
				1._F
			),
			Vector3(
				std::max(std::max(vertexA.X, vertexB.X), vertexC.X) + 0.01_F,
				std::max(std::max(vertexA.Y, vertexB.Y), vertexC.Y) + 0.01_F,
				std::max(std::max(vertexA.Z, vertexB.Z), vertexC.Z) + 0.01_F,
				1._F
			)
		);

		TrianglePartition.Insert(&Triangles[i], triangleBox);
	}
}

void MeshData::CastRay(const Ray& ray, const CastResultsCallback& callback) const
{
	TrianglePartition.CastRay(ray, [this, &ray, &callback] (const AabbTree::Node* node, Float t)
	{
		TriangleData* triangleData = node->GetData<TriangleData>();

		const Vector3Raw& vertexA = VertexBuffer[triangleData->VertexA].Position;
		const Vector3Raw& vertexB = VertexBuffer[triangleData->VertexB].Position;
		const Vector3Raw& vertexC = VertexBuffer[triangleData->VertexC].Position;

		Vector3 normal = Vector3(vertexB - vertexA).Cross(vertexC - vertexA);

		Float normalDot = normal * ray.Direction;

		if (normalDot >= 0)
			return;

		Float distance = (normal * (vertexA - ray.Start)) / normalDot;

		if (distance > 1 || distance < 0)
			return;

		Vector3 intersection = ray.Start + distance * ray.Direction;

		Float dot1 = Vector3(vertexB - vertexA).Cross(intersection - vertexA).Dot(normal);
		Float dot2 = Vector3(vertexC - vertexB).Cross(intersection - vertexB).Dot(normal);
		Float dot3 = Vector3(vertexA - vertexC).Cross(intersection - vertexC).Dot(normal);

		if (!(std::signbit(dot1) == std::signbit(dot2) && std::signbit(dot1) == std::signbit(dot3)))
			return;

		callback(SceneRayCastResults { distance, 0, intersection, normal });
	});
}

MeshData& MeshData::operator=(const MeshData& other)
{
	Mode = other.Mode;
	DrawMode = other.DrawMode;
	VertexBuffer = other.VertexBuffer;
	IndexBuffer = other.IndexBuffer;
	DrawMode = other.DrawMode;
	Minimum = other.Minimum;
	Maximum = other.Maximum;
	Triangles = other.Triangles;

	ConfigurePartitioning();

	return *this;
}

namespace
{
	typedef std::vector<int> ReferenceVector;
	typedef std::vector<ReferenceVector> ReferenceMap;
	typedef std::vector<Vector3> NormalVector;
	typedef std::vector<NormalVector> NormalMap;
}

void MeshData::Smoothen()
{
	int vertices = int(VertexBuffer.size());
	ReferenceMap references(vertices);
	NormalMap normals(vertices);

	references.resize(vertices);
	normals.resize(vertices);

	for (int i = 0; i < int(IndexBuffer.size()); ++i)
		references[IndexBuffer[i]].push_back(i / 3);

	for (int i = 0; i < vertices; ++i)
	{
		ReferenceVector& vertexReferences = references[i];
		NormalVector& vertexNormals = normals[i];

		Vector3 average;

		for (int j = 0; j < int(vertexReferences.size()); ++j)
		{
			int face = vertexReferences[j];

			Vector3 point1 = VertexBuffer[IndexBuffer[0 + face * 3]].Position;
			Vector3 point2 = VertexBuffer[IndexBuffer[1 + face * 3]].Position;
			Vector3 point3 = VertexBuffer[IndexBuffer[2 + face * 3]].Position;

			Vector3 normal = (point2 - point1).Cross(point3 - point1).Normalize();

			bool newNormal = true;

			for (int k = 0; k < int(vertexNormals.size()); ++k)
				if (vertexNormals[k] == normal)
					newNormal = false;

			if (newNormal)
			{
				vertexNormals.push_back(normal);
				average += normal;
			}
		}

		average.Normalize();

		VertexBuffer[i].Normal = average;
	}
}

void MeshData::GenerateCylinderMap(const MeshData* meshData)
{
	if (meshData->VertexBuffer.size() * 3 == meshData->IndexBuffer.size())
	{
		VertexBuffer = meshData->VertexBuffer;
		IndexBuffer = meshData->IndexBuffer;
		Triangles = meshData->Triangles;
	}
	else
	{
		for (int i = 0; i < int(meshData->IndexBuffer.size()); ++i)
		{
			VertexBuffer.push_back(meshData->VertexBuffer[meshData->IndexBuffer[i]]);
			IndexBuffer.push_back(i);

			if (i % 3 == 2)
				Triangles.push_back(TriangleData { IndexBuffer[IndexBuffer.size() - 3], IndexBuffer[IndexBuffer.size() - 2], IndexBuffer[IndexBuffer.size() - 1], int(Triangles.size()) });
		}
	}

	Minimum = meshData->Minimum;
	Maximum = meshData->Maximum;
	Mode = meshData->Mode;

	int vertices = int(VertexBuffer.size());

	Vector3 center = GetCenter();

	for (int i = 0; i < vertices; ++i)
	{
		Vector3 vector = VertexBuffer[i].Position - center;

		Float r = vector.Length();
		Float theta = std::atan2(vector.Z, vector.X);

		VertexBuffer[i].UV = Vector2Raw(0.5f - 0.5f * theta / PI, 0.5f - vector.Y / GetSize().Y);
	}

	for (int i = 0; i < vertices; i += 3)
	{
		Vector3 A = VertexBuffer[i + 0].Position;
		Vector3 B = VertexBuffer[i + 1].Position;
		Vector3 C = VertexBuffer[i + 2].Position;

		Vector3 uvA = VertexBuffer[i + 0].UV;
		Vector3 uvB = VertexBuffer[i + 1].UV;
		Vector3 uvC = VertexBuffer[i + 2].UV;

		Vector3 P = B - A;
		Vector3 Q = C - A;

		Vector3 uvP = uvB - uvA;
		Vector3 uvQ = uvC - uvA;

		Float denominator = 1.0f / (uvP.X * uvQ.Y - uvP.Y * uvQ.X);

		Vector3 tVector = denominator * (P * uvQ.Y - Q * uvP.Y);
		Vector3 bVector = denominator * (Q * uvP.X - P * uvQ.X);

		VertexBuffer[i + 0].TVector = tVector;
		VertexBuffer[i + 1].TVector = tVector;
		VertexBuffer[i + 2].TVector = tVector;

		VertexBuffer[i + 0].BVector = bVector;
		VertexBuffer[i + 1].BVector = bVector;
		VertexBuffer[i + 2].BVector = bVector;
	}

	ConfigurePartitioning();
}

void MeshData::GenerateSphereMap(const MeshData* meshData)
{
	if (meshData->VertexBuffer.size() * 3 == meshData->IndexBuffer.size())
	{
		VertexBuffer = meshData->VertexBuffer;
		IndexBuffer = meshData->IndexBuffer;
		Triangles = meshData->Triangles;
	}
	else
	{
		for (int i = 0; i < int(meshData->IndexBuffer.size()); ++i)
		{
			VertexBuffer.push_back(meshData->VertexBuffer[meshData->IndexBuffer[i]]);
			IndexBuffer.push_back(i);

			if (i % 3 == 2)
				Triangles.push_back(TriangleData { IndexBuffer[IndexBuffer.size() - 3], IndexBuffer[IndexBuffer.size() - 2], IndexBuffer[IndexBuffer.size() - 1], int(Triangles.size()) });
		}
	}

	Minimum = meshData->Minimum;
	Maximum = meshData->Maximum;
	Mode = meshData->Mode;

	int vertices = int(VertexBuffer.size());

	Vector3 center = GetCenter();

	for (int i = 0; i < vertices; ++i)
	{
		Vector3 vector = VertexBuffer[i].Position - center;

		Float r = vector.Length();
		Float theta = std::atan2(vector.Z, vector.X);
		Float phi = std::acos(vector.Y / r);

		VertexBuffer[i].UV = Vector2Raw(0.5f - 0.5f * theta / PI, phi / PI);
	}

	for (int i = 0; i < vertices; i += 3)
	{
		Vector3 A = VertexBuffer[i + 0].Position;
		Vector3 B = VertexBuffer[i + 1].Position;
		Vector3 C = VertexBuffer[i + 2].Position;

		Vector3 uvA = VertexBuffer[i + 0].UV;
		Vector3 uvB = VertexBuffer[i + 1].UV;
		Vector3 uvC = VertexBuffer[i + 2].UV;

		Vector3 P = B - A;
		Vector3 Q = C - A;

		Vector3 uvP = uvB - uvA;
		Vector3 uvQ = uvC - uvA;

		Float denominator = 1.0f / (uvP.X * uvQ.Y - uvP.Y * uvQ.X);

		Vector3 tVector = denominator * (P * uvQ.Y - Q * uvP.Y);
		Vector3 bVector = denominator * (Q * uvP.X - P * uvQ.X);

		VertexBuffer[i + 0].TVector = tVector;
		VertexBuffer[i + 1].TVector = tVector;
		VertexBuffer[i + 2].TVector = tVector;

		VertexBuffer[i + 0].BVector = bVector;
		VertexBuffer[i + 1].BVector = bVector;
		VertexBuffer[i + 2].BVector = bVector;
	}

	ConfigurePartitioning();
}

namespace
{
	Float absf(Float x)
	{
		return x < 0 ? -x : x;
	}
}

void MeshData::GenerateCubeMap(const MeshData* meshData)
{
	VertexBuffer = meshData->VertexBuffer;
	IndexBuffer = meshData->IndexBuffer;
	Triangles = meshData->Triangles;
	Minimum = meshData->Minimum;
	Maximum = meshData->Maximum;
	Mode = meshData->Mode;

	int vertices = int(IndexBuffer.size());

	Vector3 size = GetSize();
	Vector3 absoluteSize = 0.5 * Vector3(std::abs(size.X), std::abs(size.Y), std::abs(size.Z));
	
	for (int i = 0; i < vertices; ++i)
	{
		Vector3 vector = VertexBuffer[i].Normal;

		Vector3 absolute = Vector3(std::abs(vector.X), std::abs(vector.Y), std::abs(vector.Z));

		Float u = 0;
		Float v = 0;

		if (absolute.Z)

		if (absolute.X >= absolute.Y && absolute.X >= absolute.Z)
		{
			u = (vector.X < 0 ? 1 : -1) * vector.Z / absolute.X;
			v = vector.Y / absolute.X;
		}
		else if (absolute.Y >= absolute.X && absolute.Y >= absolute.Z)
		{
			u = vector.X / absolute.Y;
			v = (vector.Y < 0 ? 1 : -1) * vector.Z / absolute.Y;
		}
		else
		{
			Float denominator = absolute.Z;

			if (denominator == 0)
				denominator = 1;

			u = (vector.Z < 0 ? -1 : 1) * vector.X / denominator;
			v = vector.Y / denominator;
		}

		VertexBuffer[i].UV = Vector2Raw(0.5f * u + 0.5f, 0.5f * v + 0.5f);
	}

	ConfigurePartitioning();
}

Vector3 MeshData::GetMinimumCorner() const
{
	return Minimum;
}

Vector3 MeshData::GetMaximumCorner() const
{
	return Maximum;
}

Vector3 MeshData::GetCenter() const
{
	return 0.5 * (Minimum + Maximum);
}

Vector3 MeshData::GetSize() const
{
	return Maximum - Minimum;
}
