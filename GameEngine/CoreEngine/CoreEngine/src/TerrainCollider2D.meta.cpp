#include "TerrainCollider2D.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<TerrainCollider2D>()
		{
			Reflect<TerrainCollider2D, Physics::Collider2D>::Class
			(
				"TerrainCollider2D",
				{ "GameObject" },

				Member<Bind(&TerrainCollider2D::Axis)>("Axis"),

				Constructor(
					Overload()
				)
			);
		}
	}
}