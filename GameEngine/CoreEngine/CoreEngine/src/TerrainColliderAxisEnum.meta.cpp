#include "TerrainColliderAxisEnum.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Enum::TerrainColliderAxis>()
		{
			Reflect<Enum::TerrainColliderAxis>::Enum
			(
				"TerrainColliderAxis",
				Value<Enum::TerrainColliderAxis::XYPlane>("XYPlane"),
				Value<Enum::TerrainColliderAxis::XZPlane>("XZPlane"),
				Value<Enum::TerrainColliderAxis::ZYPlane>("ZYPlane"),

				Value<Enum::TerrainColliderAxis::YXPlane>("YXPlane"),
				Value<Enum::TerrainColliderAxis::ZXPlane>("ZXPlane"),
				Value<Enum::TerrainColliderAxis::YZPlane>("YZPlane")
			);
		}
	}
}