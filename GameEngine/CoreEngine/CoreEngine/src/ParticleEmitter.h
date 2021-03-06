#pragma once

import <functional>;

#include "ShaderPrograms.h"
#include "PointGenerator.h"
#include "Mesh.h"
#include "Aabb.h"
#include "Scene.h"

#undef min
#undef max

namespace GraphicsEngine
{
	class Camera;
	class ModelAsset;

	class Particle
	{
	public:
		Float Time;
		Float LifeTime;
		Vector3 Position;
		Vector3 Direction;
		Vector3 Size;

	private:

	};

	class EmitterConfig : public Engine::Object
	{
	public:
		Color4 Color = 0xFFFFFFFF;
		Color4 GlowColor = 0xFFFFFFFF;
		Vector3 UVScale = Vector3(1, 1);
		Vector3 UVOffset;
		Vector3 BoxScale = Vector3(1, 1, 1);
		bool CubeMapped = false;
		bool CompressedNormalMap = false;

		virtual void operator()();
	};
}

namespace GraphicsEngine
{
	class ParticleEmitter : public SceneObject
	{
	public:
		typedef std::function<void()> ConfigureShaderCallback;
		typedef std::function<void(Particle& particle, Float delta)> ParticleSpawnCallback;
		typedef std::function<bool(Particle& particle, Float delta)> ParticleUpdateCallback;
		typedef std::function<void(const Particle& particle, const std::shared_ptr<Camera>& camera, const Mesh* particleMesh)> ParticleDrawCallback;

		bool Enabled = true;
		int EmitCount = 5;
		Float EmitRate = 1;

		std::weak_ptr<Engine::ModelAsset> Asset;

		void SetMaxParticles(int count);
		void Initialize() { Particles.resize(MaxParticles); SetTicks(true); }
		void Update(Float delta);
		void Draw(const std::shared_ptr<Camera>& camera);
		void FireParticles(int count, Float delta = 0);
		bool IsTransparent() const;
		Aabb GetBoundingBox() const;
		bool HasMoved() const;
		bool IsStatic() const;

		void SetConfigure(const ConfigureShaderCallback& callback, const std::shared_ptr<Object>& object = nullptr)
		{
			ConfigureCallback = callback;
			ConfigHandle = object->Cast<EmitterConfig>();
		}

		void SetConfigure(const std::shared_ptr<EmitterConfig>& configuration)
		{
			SetConfigure(*configuration, configuration);
		}

		void SetSpawn(const ParticleSpawnCallback& callback, const std::shared_ptr<Object>& object = nullptr)
		{
			SpawnCallback = callback;
			SpawnHandle = object;
		}

		void SetUpdate(const ParticleUpdateCallback& callback, const std::shared_ptr<Object>& object = nullptr)
		{
			UpdateCallback = callback;
			UpdateHandle = object;
		}

		void SetDraw(const ParticleDrawCallback& callback, const std::shared_ptr<Object>& object = nullptr)
		{
			DrawCallback = callback;
			DrawHandle = object;
		}

		static void ConfigureShader();
		static void DefaultSpawn(Particle& particle, Float delta);
		static bool DefaultUpdate(Particle& particle, Float delta);
		static void DefaultDraw(const Particle& particle, const std::shared_ptr<Camera>& camera, const Mesh* particleMesh);

	private:
		typedef std::vector<Particle> ParticleVector;

		int MaxParticles = 10;
		int ParticlesAlive = 0;
		Float TotalLifetime = 0;
		Float LastSpawn = 0;
		Aabb BoundingBox;

		ParticleVector Particles;

		std::weak_ptr<EmitterConfig> ConfigHandle;
		std::weak_ptr<Object> SpawnHandle;
		std::weak_ptr<Object> UpdateHandle;
		std::weak_ptr<Object> DrawHandle;
		ConfigureShaderCallback ConfigureCallback = ConfigureShader;
		ParticleSpawnCallback SpawnCallback = DefaultSpawn;
		ParticleUpdateCallback UpdateCallback = DefaultUpdate;
		ParticleDrawCallback DrawCallback = DefaultDraw;

		static Aabb GetPairBounds(const Aabb& first, const Aabb& second);
	};
}

namespace GraphicsEngine
{
	class ParticleConfiguration : public Engine::Object
	{
	public:
		virtual void AttachTo(const std::shared_ptr<ParticleEmitter>& emitter) {};

		Vector3 RelativeVector(const Vector3& vector) const;
		Vector3 GetMomentum() const;
	};

	class DirectionalParticleSpawner : public ParticleConfiguration
	{
	public:
		NumberRange Speed;
		NumberRange Lifetime;
		NumberRange Scale;

		Vector3 Size = Vector3(1, 1, 1);
		Vector3 Position;
		UnitVectorGenerator DirectionGenerator;

		void AttachTo(const std::shared_ptr<ParticleEmitter>& emitter)
		{
			emitter->SetSpawn(std::ref(*this), This.lock());
		}

		void operator()(Particle& particle, Float delta);
	};

	class RisingParticleSpawner : public ParticleConfiguration
	{
	public:
		NumberRange Speed;
		NumberRange Lifetime;
		NumberRange Scale;

		Vector3 Size = Vector3(1, 1, 1);
		Vector3 Position;
		Vector3 Direction;

		UnitVectorGenerator DirectionGenerator;

		Float Radius = 1;

		void AttachTo(const std::shared_ptr<ParticleEmitter>& emitter)
		{
			emitter->SetSpawn(std::ref(*this), This.lock());
		}

		void operator()(Particle& particle, Float delta);
	};

	class PlanarParticleSpawner : public ParticleConfiguration
	{
	public:
		NumberRange Distance1;
		NumberRange Distance2;
		NumberRange Scale;
		NumberRange Speed;
		NumberRange Lifetime;

		Vector3 Axis1 = Vector3(1, 0, 0);
		Vector3 Axis2 = Vector3(0, 0, -1);
		Vector3 Size = Vector3(1, 1, 1);
		Vector3 Position;

		void AttachTo(const std::shared_ptr<ParticleEmitter>& emitter)
		{
			emitter->SetSpawn(std::ref(*this), This.lock());
		}

		void operator()(Particle& particle, Float delta);
	};

	class LineParticleSpawner : public ParticleConfiguration
	{
	public:
		NumberRange Scale;
		NumberRange Speed;
		NumberRange Lifetime;

		Vector3 Point1;
		Vector3 Point2;
		Vector3 Direction;
		Vector3 Size = Vector3(1, 1, 1);

		void AttachTo(const std::shared_ptr<ParticleEmitter>& emitter)
		{
			emitter->SetSpawn(std::ref(*this), This.lock());
		}

		void operator()(Particle& particle, Float delta);
	};

	class RingParticleSpawner : public ParticleConfiguration
	{
	public:
		NumberRange Scale;
		NumberRange Speed;
		NumberRange Lifetime;
		NumberRange Radius = NumberRange(1, 1);
		NumberRange Angle;

		Vector3 Position;
		Vector3 Normal = Vector3(0, 1, 0);
		Vector3 Size = Vector3(1, 1, 1);

		void AttachTo(const std::shared_ptr<ParticleEmitter>& emitter)
		{
			emitter->SetSpawn(std::ref(*this), This.lock());
		}

		void operator()(Particle& particle, Float delta);
	};

	class ConeParticleSpawner : public ParticleConfiguration
	{
	public:
		NumberRange Scale;
		NumberRange Speed;
		NumberRange Lifetime;
		NumberRange Angle;

		Vector3 Position;
		Vector3 Normal;
		Vector3 Size = Vector3(1, 1, 1);

		void AttachTo(const std::shared_ptr<ParticleEmitter>& emitter)
		{
			emitter->SetSpawn(std::ref(*this), This.lock());
		}

		void operator()(Particle& particle, Float delta);
	};

	class GravityParticleUpdater : public ParticleConfiguration
	{
	public:
		Vector3 Force;

		void AttachTo(const std::shared_ptr<ParticleEmitter>& emitter)
		{
			emitter->SetUpdate(std::ref(*this), This.lock());
		}

		bool operator()(Particle& particle, Float delta);
	};

	class DragParticleUpdater : public ParticleConfiguration
	{
	public:
		Float DragFactor = 1;

		void AttachTo(const std::shared_ptr<ParticleEmitter>& emitter)
		{
			emitter->SetUpdate(std::ref(*this), This.lock());
		}

		bool operator()(Particle& particle, Float delta);
	};

	class DampenedForceUpdater : public ParticleConfiguration
	{
	public:
		Float DragFactor = 1;
		Vector3 Force;

		void AttachTo(const std::shared_ptr<ParticleEmitter>& emitter)
		{
			emitter->SetUpdate(std::ref(*this), This.lock());
		}

		bool operator()(Particle& particle, Float delta);
	};

	class CubicBezierUpdater : public ParticleConfiguration
	{
	public:
		Vector3 Start;
		Vector3 Control1;
		Vector3 Control2;
		Vector3 End;
		Float FinishThreshold = 0.1f;

		void AttachTo(const std::shared_ptr<ParticleEmitter>& emitter)
		{
			emitter->SetUpdate(std::ref(*this), This.lock());
		}

		bool operator()(Particle& particle, Float delta);
	};
}
