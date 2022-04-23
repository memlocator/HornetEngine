#include "ChunkLoaderShapeEnum.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Enum::ChunkLoaderShape>()
		{
			Reflect<Enum::ChunkLoaderShape>::Enum
			(
				"ChunkLoaderShape",
				Value<Enum::ChunkLoaderShape::Box>("Box"),
				Value<Enum::ChunkLoaderShape::Sphere>("Sphere"),
				Value<Enum::ChunkLoaderShape::CylinderX>("CylinderX"),
				Value<Enum::ChunkLoaderShape::CylinderY>("CylinderY"),
				Value<Enum::ChunkLoaderShape::CylinderZ>("CylinderZ")
			);
		}
	}
}