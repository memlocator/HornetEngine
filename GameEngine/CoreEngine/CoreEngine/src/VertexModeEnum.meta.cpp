#include "VertexModeEnum.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Enum::VertexMode>()
		{
			Reflect<Enum::VertexMode>::Enum
			(
				"VertexMode",
				Value<Enum::VertexMode::Seperate>("Seperate"),
				Value<Enum::VertexMode::Shared>("Shared"),
				Value<Enum::VertexMode::Smoothened>("Smoothened"),
				Value<Enum::VertexMode::Wireframe>("Wireframe")
			);
		}
	}
}