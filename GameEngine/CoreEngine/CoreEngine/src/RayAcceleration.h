#include <vector>
#include <map>
#include <memory>
#include <functional>

#include "Vector3.h"
#include "RGBA.h"
#include "AabbTree.h"
#include "Light.h"
#include "AcceleratedKDTree.h"

class Ray;
class MeshData;

namespace GraphicsEngine
{
	class Scene;
	class PhysicalMaterial;

	struct RayFilterResultsEnum
	{
		enum RayFilterResults
		{
			Ignore,
			Confirm,
			Stop
		};
	};

	typedef RayFilterResultsEnum::RayFilterResults RayFilterResults;

	class RayAcceleration
	{
	public:
		typedef std::vector<int> IndexVector;

		class Material
		{
		public:
			RGBA Albedo = RGBA(1.f, 1.f, 1.f, 1.f);
			Float Roughness = 0.5f;
			Float Metalness = 0;
			Float RefractiveIndex = 1.1f;
			Float Transparency = 0; // (1 - transparency) * diffuse; transparency * transmitted
			Float Translucency = 0.01f; // light loss from travel distance
			Float Emission = 0;
		};

		class CastResults
		{
		public:
			bool HitFront = false;
			Float Distance = -1;
			const Material* MaterialProperties = nullptr;
			int ObjectID = -1;
			int ObjectNode = -1;
			int FaceIndex = -1;
			int NodeID = -1;
			Vector3 Color;
			Vector BaryCentric = Vector(0, 0, 0);
			Vector3 Normal;
			Vector3 Intersection;
			Vector3 GlowColor;

			bool operator<(const CastResults& other)
			{
				if (Distance == -1)
					return false;

				return Distance > other.Distance;
			}
		};

		struct TraversalStep
		{
			int Index = -1;
			Float Distance = 1;
		};

		typedef std::vector<TraversalStep> TraversalVector;

		struct TraversalQueue
		{
			TraversalVector ObjectQueue;
			TraversalVector TriangleQueue;
		};

		typedef std::function<RayFilterResults(const CastResults& results)> ResultsCallback;

		class Matrix
		{
		public:
			Float Data[3][3] = {};
		};

		class Object
		{
		public:
			int Mesh = -1;
			int MaterialProperties = -1;
			Vector Color;
			Vector GlowColor;
			Vector Position;
			Vector InverseOffset;
			Matrix Transformation;
			Matrix NormalTransformation;
			Matrix InverseTransformation;
		};

		class FastRay
		{
		public:
			FastRay() {}

			FastRay(const Ray& ray) : Start{ ray.Start.X, ray.Start.Y, ray.Start.Z }, Direction{ ray.Direction.X, ray.Direction.Y, ray.Direction.Z }
			{
				InverseDirection = Vector{
					1 / ray.Direction.X,
					1 / ray.Direction.Y,
					1 / ray.Direction.Z
				};
			}

			FastRay(const Vector3& start, const Vector3& direction) : Start{ start.X, start.Y, start.Z }, Direction{ direction.X, direction.Y, direction.Z }
			{
				InverseDirection = Vector{
					1 / direction.X,
					1 / direction.Y,
					1 / direction.Z
				};
			}

			FastRay(const Vector& start, const Vector& direction) : Start{ start.X, start.Y, start.Z }, Direction{ direction.X, direction.Y, direction.Z }
			{
				InverseDirection = Vector{
					1 / direction.X,
					1 / direction.Y,
					1 / direction.Z
				};
			}

			Vector Start, Direction;
			Vector InverseDirection;
		};

		class RayTest
		{
		public:
			FastRay LocalRay = FastRay{Vector3(), Vector3()};
			int Object = -1;
		};

		class Light
		{
		public:
			Float Range = 0;
			Float Brightness = 1;
			Float Radius = 0;
			Float InnerRadius = PI / 5;
			Float OuterRadius = PI / 3;
			Float AttenuationOffset = 0;
			int SpotlightFalloff = 1;
			Enum::LightType Type = Enum::LightType::Directional;
			Vector Attenuation = Vector(0, 0, 0);
			Vector Position = Vector(0, 0, 0);
			Vector Direction = Vector(0, 0, 0);
			Vector Color = Vector(1, 1, 1);

			Float GetRadius() const { return Radius; }
			Float GetAttenuationOffset() const { return AttenuationOffset; }
		};

		typedef std::vector<RayTest> RayTestVector;

		void Accelerate(const std::shared_ptr<Scene>& scene);
		void CastRay(const Ray& ray, Float length, const ResultsCallback& callback, const ResultsCallback& filter, IndexVector& stack, int startObjectNode = -1, int startNode = -1) const;
		const Light* GetLight(int index) const { if (index == -1) return GlobalLight; return &Lights[index]; }
		int GetLights() const { return int(Lights.size()); }
		const Light* GetDirectionalLight(int index) const { if (index == -1) return GlobalLight; return &Lights[DirectionalLights[index]]; }
		int GetDirectionalLights() const { return int(DirectionalLights.size()); }
		void UpdateMaterials();

	private:

		typedef std::vector<Material> MaterialVector;
		typedef std::vector<Mesh> MeshVector;
		typedef std::vector<int> MeshDataVector;
		typedef std::vector<TreeNode> NodeVector;
		typedef std::vector<Object> ObjectVector;
		typedef std::map<const void*, int> IndexMap;
		typedef std::vector<Vertex> VertexVector;
		typedef std::vector<Face> FaceVector;
		typedef std::function<void(int, int)> ObjectCallback;
		typedef std::vector<Light> LightVector;
		typedef std::vector<KDNode> KDNodeVector;
		typedef std::map<GraphicsEngine::PhysicalMaterial*, int> MaterialMap;

		MaterialVector Materials;
		MeshVector Meshes;
		MeshDataVector MeshIds;
		NodeVector Nodes;
		KDNodeVector KDNodes;
		ObjectVector Objects;
		IndexMap Indices;
		MaterialMap MaterialCache;
		VertexVector Vertices;
		FaceVector Faces;
		LightVector Lights;
		IndexVector DirectionalLights;

		Light* GlobalLight = nullptr;

		int ObjectTreeHead = -1;
		int LightTreeHead = -1;

		int MeshLeftNodes = 0;
		int MeshRightNodes = 0;

		void CastRay(int node, const Ray& ray, Float& farthest, const ObjectCallback& callback, IndexVector& stack) const;
		void ProcessRay(int node, const Ray& ray, Float& farthest, const ObjectCallback& callback) const;
		int PushMesh(const MeshData* data, int id, const std::string& name);
		int PushMaterial(const std::shared_ptr<GraphicsEngine::PhysicalMaterial>& material);
		void PushNode(const AabbTree::Node* node, bool isDynamic, const std::shared_ptr<Scene>& scene);
		void PushMeshNode(const AabbTree::Node* node, int meshIndex);
	};
}