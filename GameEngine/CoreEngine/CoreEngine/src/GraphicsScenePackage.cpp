#include "GraphicsScenePackage.h"

#include "Camera.h"
#include "SceneRayCastResults.h"
#include "Material.h"
#include "Light.h"
#include "Scene.h"
#include "Model.h"
#include "PhysicalMaterial.h"
#include "ModelAsset.h"
#include "VertexModeEnum.h"
#include "ParticleEmitter.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		extern void ReflectType<GraphicsEngine::Camera>();
		
		template <>
		extern void ReflectType<GraphicsEngine::Material>();
		
		template <>
		extern void ReflectType<GraphicsEngine::Light>();
		
		template <>
		extern void ReflectType<GraphicsEngine::PhysicalMaterial>();
		
		template <>
		extern void ReflectType<GraphicsEngine::SceneObject>();
		
		template <>
		extern void ReflectType<GraphicsEngine::Scene>();
		
		template <>
		extern void ReflectType<GraphicsEngine::Model>();
		
		template <>
		extern void ReflectType<GraphicsEngine::ModelAsset>();
		
		template <>
		extern void ReflectType<GraphicsEngine::EmitterConfig>();
		
		template <>
		extern void ReflectType<GraphicsEngine::ParticleEmitter>();
		
		template <>
		extern void ReflectType<GraphicsEngine::ParticleConfiguration>();
		
		template <>
		extern void ReflectType<GraphicsEngine::DirectionalParticleSpawner>();
		
		template <>
		extern void ReflectType<GraphicsEngine::RisingParticleSpawner>();
		
		template <>
		extern void ReflectType<GraphicsEngine::PlanarParticleSpawner>();
		
		template <>
		extern void ReflectType<GraphicsEngine::LineParticleSpawner>();
		
		template <>
		extern void ReflectType<GraphicsEngine::RingParticleSpawner>();
		
		template <>
		extern void ReflectType<GraphicsEngine::ConeParticleSpawner>();
		
		template <>
		extern void ReflectType<GraphicsEngine::GravityParticleUpdater>();
		
		template <>
		extern void ReflectType<GraphicsEngine::DragParticleUpdater>();
		
		template <>
		extern void ReflectType<GraphicsEngine::DampenedForceUpdater>();
		
		template <>
		extern void ReflectType<GraphicsEngine::CubicBezierUpdater>();
		
		template <>
		extern void ReflectType<SceneRayCastResults>();
		
		template <>
		extern void ReflectType<Enum::LightDirection>();
		
		template <>
		extern void ReflectType<Enum::LightType>();
		
		template <>
		extern void ReflectType<Enum::VertexMode>();

		template <>
		void ReflectPackage<GraphicsScenePackage>()
		{
			ReflectFromPackage<
				GraphicsEngine::Camera,
				GraphicsEngine::Material,
				GraphicsEngine::Light,
				GraphicsEngine::PhysicalMaterial,
				GraphicsEngine::SceneObject,
				GraphicsEngine::Scene,
				GraphicsEngine::Model,
				GraphicsEngine::EmitterConfig,
				GraphicsEngine::ParticleEmitter,
				GraphicsEngine::ParticleConfiguration,
				GraphicsEngine::DirectionalParticleSpawner,
				GraphicsEngine::RisingParticleSpawner,
				GraphicsEngine::PlanarParticleSpawner,
				GraphicsEngine::LineParticleSpawner,
				GraphicsEngine::RingParticleSpawner,
				GraphicsEngine::ConeParticleSpawner,
				GraphicsEngine::GravityParticleUpdater,
				GraphicsEngine::DragParticleUpdater,
				GraphicsEngine::DampenedForceUpdater,
				GraphicsEngine::CubicBezierUpdater,
				ModelAsset,
				SceneRayCastResults,
				Enum::LightDirection,
				Enum::LightType,
				Enum::VertexMode
			>();
		}
	}
}