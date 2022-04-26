#include "ColliderAsset.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace Engine::Physics;

		template <>
		void ReflectType<ColliderAsset>()
		{
			Reflect<ColliderAsset, Object>::Class
			(
				"ColliderAsset",
				{ "GameObject", "Physics" },

				Constructor(
					Overload()
				),

				Function(
					"ConfigureTriangleMesh",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<ColliderAsset, &ColliderAsset::ConfigureTriangleMesh>()
				),

				Function(
					"ConfigureSquareMesh",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<ColliderAsset, &ColliderAsset::ConfigureSquareMesh>()
				),

				Function(
					"ConfigureOctagonMesh",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<ColliderAsset, &ColliderAsset::ConfigureOctagonMesh>()
				),

				Function(
					"ConfigureShipMesh",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<ColliderAsset, &ColliderAsset::ConfigureShipMesh>()
				),

				Function(
					"ConfigureChargerShieldMesh",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<ColliderAsset, &ColliderAsset::ConfigureChargerShieldMesh>()
				),

				Function(
					"ConfigureWormHeadMesh",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<ColliderAsset, &ColliderAsset::ConfigureWormHeadMesh>()
				),

				Function(
					"ConfigureWormTailMesh",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<ColliderAsset, &ColliderAsset::ConfigureWormTailMesh>()
				)
			);
		}
	}
}