#pragma once

import <memory>;
import <string>;
import <thread>;
import <algorithm>;
import <chrono>;
import <mutex>;
import <random>;

#include "Object.h"
#include "Color4.h"
#include "Ray.h"
#include "SceneRayCastResults.h"
#include "RayAcceleration.h"

#define USE_SANITY_CHECKS 0

#if USE_SANITY_CHECKS
#define CHECK_VALUE(value) ValidateData(value, __FILE__, __LINE__)
#else
#define CHECK_VALUE(value) value
#endif

namespace GraphicsEngine
{
	class Texture;
	class Scene;
	class Camera;
	class Light;
	struct RayCastData;
	struct ShadowCastData;

	struct Pixel
	{
		float R = 0;
		float G = 0;
		float B = 0;

		Pixel() {}
		Pixel(const Color4& color);
		Pixel(unsigned char R, unsigned char G, unsigned char B) : R(float(R) / 255.0f), G(float(G) / 255.0f), B(float(B) / 255.0f) {}
		Pixel(float R, float G, float B) : R(R), G(G), B(B) {}
		Pixel(double R, double G, double B) : R((float)R), G((float)G), B((float)B) {}

		operator Color4();
	};

	class RayTracer : public Engine::Object
	{
	public:
		typedef RayAcceleration::CastResults CastResults;
		typedef RayAcceleration::Material Material;
		typedef const RayAcceleration::Light* LightHandle;
		typedef std::vector<CastResults> ResultsQueue;
		typedef RayAcceleration::ResultsCallback ResultsCallback;

		struct RayInfo
		{
			int ObjectNode = -1;
			int NodeID = -1;
			int FaceIndex = -1;
		};

		static inline const int CoreCount = int(std::thread::hardware_concurrency());
		static inline const bool PerformAnalytics = false;
		static inline const bool ComputeAsync = false;
		static inline const bool DisplayOutput = true;
		static inline const bool RenderAtmosphere = false;
		static inline const bool RenderNaiveAtmosphere = true;
		static inline const bool UseMicrofacetNormals = true;
		static inline const bool UseDepthTest = false;
		static inline const bool ComputeShadows = false;

		int BatchWidth = 64;
		int BatchHeight = 64;
		int MaxBounces = 5;
		int Samples = 10;
		bool Initialized = false;

		bool AtmosphereFollowsCamera = false;
		Float PlanetRadius = 6378131*01;
		Float AtmosphereHeight = 256000 * 01;
		Float Altitude = 210000 * 01;
		int AtmosphereSteps = 10;
		int OpticalDepthSteps = 10;
		Float AtmosphericDensityFalloff = 10;
		Vector3 PlanetDirection = Vector3(0, -1, 0);
		Vector3 Wavelengths = Vector3(700, 530, 400);
		Float ScatterStrength = 1;
		int MouseX = 0;
		int MouseY = 0;

		std::weak_ptr<Scene> CurrentScene;

		~RayTracer();

		void SetMaxThreads(int count);
		int GetMaxThreads() const;
		int GetHardwareThreads() const { return CoreCount; }
		void Configure(int width, int height);
		void SetViewport(int minX, int minY, int maxX, int maxY);
		void Render();
		void DrawTo(const std::shared_ptr<Texture>& output) const;
		void Save(const std::string& filePath) const;

		int GetIndex(int x, int y) const;
		const Pixel& GetPixel(int x, int y) const;
		Pixel& GetPixel(int x, int y);
		void SetPixel(int x, int y, const Pixel& pixel);

	private:
		friend struct RayCastData;
		
		struct QueuedRay
		{
			int Bounces = 0;
			int RayID = 0;
			int LastFace = -1;
			int LastObject = -1;
			Vector3 LightFilter;
			Ray Data;
			Float Length = 1;
		};

		typedef std::function<void(const CastResults& results)> CastResultsCallbackWrapper;
		typedef std::vector<QueuedRay> RayVector;
		typedef std::vector<RayInfo> RayInfoVector;
		typedef std::vector<RayInfoVector> RayLightVector;
		
		struct FloatRNG
		{
			std::random_device RandomDevice;
			std::mt19937 RandomAlgorithm = std::mt19937(RandomDevice());
			std::uniform_real_distribution<Float> RNG = std::uniform_real_distribution<Float>(0, 1);

			Float Next()
			{
				return RNG(RandomAlgorithm);
			}
		};

		long long RayCount = 0;
		long long BounceRayCount = 0;
		long long ShadowRayCount = 0;
		long long LightsChecked = 0;
		long long FailedLights = 0;
		long long BouncesChecked = 0;
		int MinX = 0;
		int MinY = 0;
		int MaxX = 0;
		int MaxY = 0;
		int Width = 0;
		int Height = 0;	
		int RayWidth = 0;
		int RayHeight = 0;
		Pixel* Data = nullptr;
		Float* DepthBuffer = nullptr;
		int MaxThreads = 1;
		int RunningThreads = 0;
		int MaxRunningThreads = 0;
		std::shared_ptr<const Camera> ThisCamera;
		std::shared_ptr<const Scene> ThisScene;
		std::shared_ptr<Light> GlobalLight;
		RayAcceleration Accelerator;
		Vector* Rays = nullptr;

		Vector3 PlanetPosition;
		Float AtmosphereRadius = 0;
		Float AtmosphereRadiusSquared = 0;
		Float PlanetRadiusSquared = 0;
		Float AtmosphereStep = 0;
		Float OpticalDepthStep = 0;
		Vector3 ScatterCoefficients;

		std::mutex BatchLock;
		int NextX = 0;
		int NextY = 0;

		struct Batch
		{
			int X = 0;
			int Y = 0;
		};

		Batch GetNext();

		typedef std::vector<int> IndexVector;

		struct Thread
		{
			std::chrono::steady_clock::time_point ThreadStarted;
			std::chrono::nanoseconds ThreadTotal = std::chrono::nanoseconds();
			long long RayCount = 0;
			long long BounceRayCount = 0;
			long long ShadowRayCount = 0;
			long long LightsChecked = 0;
			long long FailedLights = 0;
			long long BouncesChecked = 0;
			bool Finished = false;
			bool Allocated = false;
			int LastBounces = -1;
			RayInfoVector RayCache;
			RayInfoVector RayShadowCache;
			char Buffer[sizeof(std::thread)] = {};
			std::thread* ThreadData = reinterpret_cast<std::thread*>(Buffer);
			RayVector QueuedRays;
			IndexVector RayStack;

			FloatRNG RNG;

			int RayX = 0;
			int RayY = 0;

			~Thread();

			void Spawn(RayTracer* rayTracer, int x, int y, int threadID);
			void SpawnSync(RayTracer* rayTracer, int threadID);
			void Free(RayTracer* rayTracer = nullptr);
		};

		struct LightingParameters
		{
			Float LookDot;
			const Material* MaterialProperties;
			Vector3 Intersection;
			Vector3 Normal;
			Vector3 Color;
			Vector3 Diffuse;
			Vector3 Look;
			Vector3 BaseReflectivity;
			Float LookRoughness;
			Float LightRoughness;
			Float QuadRoughness;
		};

		struct SphereIntersection
		{
			Float Entry = 0;
			Float Exit = 0;
			Float Surface = 0;
		};

		Thread* Threads = new Thread[1] {};

		void Cast(const RayInfo& info, const Ray& ray, Float length, const ResultsCallback& callback, const ResultsCallback& filter, IndexVector& stack) const;
		void CastRay(RayInfo& info, const Ray& ray, const RayCastData& rayData, const CastResultsCallbackWrapper& callback, IndexVector& stack) const;

		int GetLights() const;
		LightHandle GetLight(int index) const;

		int GetDirectionalLights() const;
		LightHandle GetDirectionalLight(int index) const;

		void QueueRay(Thread& thread, const QueuedRay& ray) const;

		Float Fresnel(Float dot, Float internalRefractiveIndex, Float externalRefractiveIndex = 1) const;
		Vector3 RefractVector(const Vector3& vector, const Vector3& normal, Float dot, Float internalRefractiveIndex, Float externalRefractiveIndex = 1) const;
		Vector3 ReflectVector(const Vector3& vector, const Vector3& normal) const;
		Vector3 ReflectVector(Float dot, const Vector3& vector, const Vector3& normal) const;
		Ray GetRay(int x, int y) const;
		Vector3 ComputeLightFilter(const Vector3& color, const Vector3& filter) const;	
		Vector3 ComputeShadowFilter(const Ray& ray, Float length, RayInfo& info, const ShadowCastData& shadowData, IndexVector& stack) const;
		Float NormalDistribution(Float reflectedDot, Float roughness) const;
		Float GeometryShadowing(Float vectorDot, Float roughness) const;
		Float GeometryContribution(Float lookDot, Float lightDot, Float roughness) const;
		Float Largest(const Vector3& vector) const;
		Float Smallest(const Vector3& vector) const;
		Vector3 SampleNormal(FloatRNG& rng, const Vector3& normal, const Vector3& view, Float roughness) const;
		Vector3 ComputeReflectionFilter(const Vector3& direction, const Vector3& reflected, const Vector3& normal, const Vector3& microfacetNormal, const Vector3& baseReflectivity, Float roughnessSquared) const;
		Vector3 BaseReflectivity(Float metalness, Float refractiveIndex, Float externalIndex, const Vector3& color, Float dot = 1) const;
		Vector3 FresnelSchlick(Float reflectedDot, const Vector3& baseReflectivity) const;
		Vector3 GetReflectionFilter(const Material* material, Float reflectedDot, Float lookDot, Float lightDot, const Vector3& baseReflectivity) const;
		Vector3 GetRefractionFilter(const Material* material, Float lightDot, const Vector3& color, const Vector3& baseReflectivity, const Vector3& lightFilter) const;
		Vector3 CookTorranceBRDF(const LightingParameters& parameters, Float reflectedDot, Float lightDot) const;
		Vector3 ComputeLighting(const LightingParameters& parameters, LightHandle light, const Vector3& lightFilter, RayInfo& info, const ShadowCastData& shadowData, Thread& thread) const;
		SphereIntersection ComputeAtmosphereIntersection(const Ray& ray) const;
		Float ComputeSunRayLength(LightHandle light, const Vector3& position) const;
		Float ComputeOpticalDepth(const Vector3& scatterPoint, const Vector3& direction, Float rayLength) const;
		Float ComputeAtmosphericDensity(const Vector3& scatterPoint) const;
		Vector3 ComputeAtmosphericLight(LightHandle light, const Ray& ray, const SphereIntersection& intersection) const;
		Vector3 ComputeAtmosphericLightNaive(const Vector3& direction) const;
		Vector3 ProcessRay(const QueuedRay& ray, Thread& thread, const Vector3& lightFilter, int bounces = 0, int rayID = 0) const;
		void ProcessBatch(int x, int y, int threadID);
		void DrawLine(const Vector3& start, const Vector3& end, const Color4& color);
	};
}