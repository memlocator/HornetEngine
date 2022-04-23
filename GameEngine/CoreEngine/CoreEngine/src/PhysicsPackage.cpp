#include "PhysicsPackage.h"

#include "TerrainColliderAxisEnum.h"
#include "Collider2D.h"
#include "ColliderAsset.h"
#include "CollisionGroup.h"
#include "PhysicsEnvironment.h"
#include "PointMass.h"
#include "RigidBody.h"
#include "TerrainCollider2D.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace Engine::Physics;

		template <>
		extern void ReflectType<Enum::TerrainColliderAxis>();
		
		template <>
		extern void ReflectType<Enum::InteractionType>();

		template <>
		extern void ReflectType<Collision>();

		template <>
		extern void ReflectType<Collider2D>();

		template <>
		extern void ReflectType<CollisionPair>();

		template <>
		extern void ReflectType<ColliderAsset>();

		template <>
		extern void ReflectType<CollisionGroup>();

		template <>
		extern void ReflectType<RayCastResults>();

		template <>
		extern void ReflectType<PhysicsEnvironment>();

		template <>
		extern void ReflectType<PointMass>();

		template <>
		extern void ReflectType<RigidBody>();

		template <>
		extern void ReflectType<TerrainCollider2D>();

		template <>
		void ReflectPackage<PhysicsPackage>()
		{
			ReflectFromPackage<
				Enum::TerrainColliderAxis,
				Enum::InteractionType,
				Collision,
				Collider2D,
				CollisionPair,
				ColliderAsset,
				CollisionGroup,
				RayCastResults,
				PhysicsEnvironment,
				PointMass,
				RigidBody,
				TerrainCollider2D
			>();
		}
	}
}