#include "TerrainMaterial.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<TerrainMaterial>()
		{
			Reflect<TerrainMaterial, Object>::Class
			(
				"TerrainMaterial",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Function(
					"GetID",
					Overload(
						Const,
						Returns<unsigned short>()
					).Bind<TerrainMaterial, &TerrainMaterial::GetID>()
				)
			);
		}
	}
}