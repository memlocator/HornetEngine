#include "Terrain2DCollider.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Terrain2DCollider>()
		{
			Reflect<Terrain2DCollider, Physics::Collider2D>::Class
			(
				"Terrain2DCollider",
				{ "GameObject" },

				Constructor(
					Overload()
				)
			);
		}
	}
}