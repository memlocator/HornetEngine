#include "PhysicsEnvironment.h"

#include "Terrain2DCollider.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace Engine::Physics;

		template <>
		void ReflectType<RayCastResults>()
		{
			Reflect<RayCastResults>::Type
			(
				"RayCastResults",

				Constructor(
					Overload()
				),

				Function(
					"GetCount",
					Overload(
						Const,
						Returns<int>()
					).Bind<RayCastResults, &RayCastResults::GetCount>()
				),

				Function(
					"GetHit",
					Overload(
						Const,
						Returns<std::shared_ptr<Collider2D>>(),
						Argument<int>("index")
					).Bind<RayCastResults, &RayCastResults::GetHit>()
				),

				Function(
					"GetDistance",
					Overload(
						Const,
						Returns<Float>(),
						Argument<int>("index")
					).Bind<RayCastResults, &RayCastResults::GetDistance>()
				),

				Function(
					"GetNormal",
					Overload(
						Const,
						Returns<Vector3>(),
						Argument<int>("index")
					).Bind<RayCastResults, &RayCastResults::GetNormal>()
				),

				Function(
					"Push",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Collider2D>&>("collider"),
						Argument<Float>("distance"),
						Argument<const Vector3&>("normal")
					).Bind<RayCastResults, &RayCastResults::Push>()
				)
			);
		}

		template <>
		void ReflectType<PhysicsEnvironment>()
		{
			Reflect<PhysicsEnvironment, Object>::Class
			(
				"PhysicsEnvironment",
				{ "GameObject", "Physics" },

				Constructor(
					Overload()
				),

				Function(
					"AddObject",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Collider2D>&>("collider")
					).Bind<PhysicsEnvironment, &PhysicsEnvironment::AddObject>()
				),

				Function(
					"RemoveObject",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Collider2D>&>("collider")
					).Bind<PhysicsEnvironment, &PhysicsEnvironment::RemoveObject>()
				),

				Function(
					"AddTerrain",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Terrain2DCollider>&>("collider")
					).Bind<PhysicsEnvironment, &PhysicsEnvironment::AddTerrain>()
				),

				Function(
					"RemoveTerrain",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Terrain2DCollider>&>("collider")
					).Bind<PhysicsEnvironment, &PhysicsEnvironment::RemoveTerrain>()
				),

				Function(
					"CastRay",
					Overload(
						Mutable,
						Returns<RayCastResults>(),
						Argument<const Ray&>("ray")
					).Bind<PhysicsEnvironment, &PhysicsEnvironment::CastRay>()
				)
			);
		}
	}
}