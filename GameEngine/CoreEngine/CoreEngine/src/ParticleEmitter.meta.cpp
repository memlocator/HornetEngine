#include "ParticleEmitter.h"

#include "ModelAsset.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<EmitterConfig>()
		{
			Reflect<EmitterConfig, Object>::Class
			(
				"EmitterConfig",
				{ "GameObject" },

				Member<Bind(&EmitterConfig::Color)>("Color"),
				Member<Bind(&EmitterConfig::Color)>("GlowColor"),
				Member<Bind(&EmitterConfig::Color)>("UVScale"),
				Member<Bind(&EmitterConfig::Color)>("UVOffset"),
				Member<Bind(&EmitterConfig::Color)>("BoxScale"),
				Member<Bind(&EmitterConfig::Color)>("CubeMapped"),
				Member<Bind(&EmitterConfig::Color)>("CompressedNormalMap"),

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<ParticleEmitter>()
		{
			Reflect<ParticleEmitter, SceneObject>::Class
			(
				"ParticleEmitter",
				{ "GameObject" },

				Member<Bind(&ParticleEmitter::Enabled)>("Enabled"),
				Member<Bind(&ParticleEmitter::EmitCount)>("EmitCount"),
				Member<Bind(&ParticleEmitter::EmitRate)>("EmitRate"),

				Member<Bind(&ParticleEmitter::Asset)>("Asset"),

				Constructor(
					Overload()
				),

				Function(
					"SetMaxParticles",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<int>("count")
					).Bind<ParticleEmitter, &ParticleEmitter::SetMaxParticles>()
				),

				Function(
					"FireParticles",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<int>("count"),
						Argument<Float, Default(0.0f)>("delta")
					).Bind<ParticleEmitter, &ParticleEmitter::FireParticles>()
				),

				Function(
					"SetConfigure",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<EmitterConfig>&>("config")
					).Bind<ParticleEmitter, &ParticleEmitter::SetConfigure>()
				)
			);
		}

		template <>
		void ReflectType<ParticleConfiguration>()
		{
			Reflect<ParticleConfiguration, Object>::Class
			(
				"ParticleConfiguration",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Function(
					"AttachTo",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<ParticleEmitter>&>("emitter")
					).Bind<ParticleConfiguration, &ParticleConfiguration::AttachTo>()
				),

				Function(
					"RelativeVector",
					Overload(
						Const,
						Returns<Vector3>(),
						Argument<const Vector3&>("emitter")
					).Bind<ParticleConfiguration, &ParticleConfiguration::RelativeVector>()
				),

				Function(
					"GetMomentum",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<ParticleConfiguration, &ParticleConfiguration::GetMomentum>()
				)
			);
		}

		template <>
		void ReflectType<DirectionalParticleSpawner>()
		{
			Reflect<DirectionalParticleSpawner, ParticleConfiguration>::Class
			(
				"DirectionalParticleSpawner",
				{ "GameObject" },

				Member<Bind(&DirectionalParticleSpawner::Speed)>("Speed"),
				Member<Bind(&DirectionalParticleSpawner::Lifetime)>("Lifetime"),
				Member<Bind(&DirectionalParticleSpawner::Scale)>("Scale"),

				Member<Bind(&DirectionalParticleSpawner::Size)>("Size"),
				Member<Bind(&DirectionalParticleSpawner::Position)>("Position"),
				Member<Bind(&DirectionalParticleSpawner::DirectionGenerator)>("DirectionGenerator"),

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<RisingParticleSpawner>()
		{
			Reflect<RisingParticleSpawner, ParticleConfiguration>::Class
			(
				"RisingParticleSpawner",
				{ "GameObject" },

				Member<Bind(&RisingParticleSpawner::Speed)>("Speed"),
				Member<Bind(&RisingParticleSpawner::Lifetime)>("Lifetime"),
				Member<Bind(&RisingParticleSpawner::Scale)>("Scale"),

				Member<Bind(&RisingParticleSpawner::Size)>("Size"),
				Member<Bind(&RisingParticleSpawner::Position)>("Position"),
				Member<Bind(&RisingParticleSpawner::Direction)>("Direction"),

				Member<Bind(&RisingParticleSpawner::DirectionGenerator)>("DirectionGenerator"),

				Member<Bind(&RisingParticleSpawner::Radius)>("Radius"),

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<PlanarParticleSpawner>()
		{
			Reflect<PlanarParticleSpawner, ParticleConfiguration>::Class
			(
				"PlanarParticleSpawner",
				{ "GameObject" },

				Member<Bind(&PlanarParticleSpawner::Distance1)>("Distance1"),
				Member<Bind(&PlanarParticleSpawner::Distance2)>("Distance2"),
				Member<Bind(&PlanarParticleSpawner::Speed)>("Speed"),
				Member<Bind(&PlanarParticleSpawner::Lifetime)>("Lifetime"),
				Member<Bind(&PlanarParticleSpawner::Scale)>("Scale"),

				Member<Bind(&PlanarParticleSpawner::Axis1)>("Axis1"),
				Member<Bind(&PlanarParticleSpawner::Axis2)>("Axis2"),
				Member<Bind(&PlanarParticleSpawner::Size)>("Size"),
				Member<Bind(&PlanarParticleSpawner::Position)>("Position"),

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<LineParticleSpawner>()
		{
			Reflect<LineParticleSpawner, ParticleConfiguration>::Class
			(
				"LineParticleSpawner",
				{ "GameObject" },

				Member<Bind(&LineParticleSpawner::Speed)>("Speed"),
				Member<Bind(&LineParticleSpawner::Lifetime)>("Lifetime"),
				Member<Bind(&LineParticleSpawner::Scale)>("Scale"),

				Member<Bind(&LineParticleSpawner::Point1)>("Point1"),
				Member<Bind(&LineParticleSpawner::Point2)>("Point2"),
				Member<Bind(&LineParticleSpawner::Size)>("Size"),
				Member<Bind(&LineParticleSpawner::Direction)>("Direction"),

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<RingParticleSpawner>()
		{
			Reflect<RingParticleSpawner, ParticleConfiguration>::Class
			(
				"RingParticleSpawner",
				{ "GameObject" },

				Member<Bind(&RingParticleSpawner::Speed)>("Speed"),
				Member<Bind(&RingParticleSpawner::Lifetime)>("Lifetime"),
				Member<Bind(&RingParticleSpawner::Scale)>("Scale"),
				Member<Bind(&RingParticleSpawner::Radius)>("Radius"),
				Member<Bind(&RingParticleSpawner::Angle)>("Angle"),

				Member<Bind(&RingParticleSpawner::Position)>("Position"),
				Member<Bind(&RingParticleSpawner::Size)>("Size"),
				Member<Bind(&RingParticleSpawner::Normal)>("Normal"),

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<ConeParticleSpawner>()
		{
			Reflect<ConeParticleSpawner, ParticleConfiguration>::Class
			(
				"ConeParticleSpawner",
				{ "GameObject" },

				Member<Bind(&ConeParticleSpawner::Speed)>("Speed"),
				Member<Bind(&ConeParticleSpawner::Lifetime)>("Lifetime"),
				Member<Bind(&ConeParticleSpawner::Scale)>("Scale"),
				Member<Bind(&ConeParticleSpawner::Angle)>("Angle"),

				Member<Bind(&ConeParticleSpawner::Position)>("Position"),
				Member<Bind(&ConeParticleSpawner::Size)>("Size"),
				Member<Bind(&ConeParticleSpawner::Normal)>("Normal"),

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<GravityParticleUpdater>()
		{
			Reflect<GravityParticleUpdater, ParticleConfiguration>::Class
			(
				"GravityParticleUpdater",
				{ "GameObject" },

				Member<Bind(&GravityParticleUpdater::Force)>("Force"),

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<DragParticleUpdater>()
		{
			Reflect<DragParticleUpdater, ParticleConfiguration>::Class
			(
				"DragParticleUpdater",
				{ "GameObject" },

				Member<Bind(&DragParticleUpdater::DragFactor)>("DragFactor"),

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<DampenedForceUpdater>()
		{
			Reflect<DampenedForceUpdater, ParticleConfiguration>::Class
			(
				"DampenedForceUpdater",
				{ "GameObject" },

				Member<Bind(&DampenedForceUpdater::DragFactor)>("DragFactor"),
				Member<Bind(&DampenedForceUpdater::Force)>("Force"),

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<CubicBezierUpdater>()
		{
			Reflect<CubicBezierUpdater, ParticleConfiguration>::Class
			(
				"DampenedForceUpdater",
				{ "GameObject" },

				Member<Bind(&CubicBezierUpdater::Start)>("Start"),
				Member<Bind(&CubicBezierUpdater::Control1)>("Control1"),
				Member<Bind(&CubicBezierUpdater::Control2)>("Control2"),
				Member<Bind(&CubicBezierUpdater::End)>("End"),
				Member<Bind(&CubicBezierUpdater::FinishThreshold)>("FinishThreshold"),

				Constructor(
					Overload()
				)
			);
		}
	}
}