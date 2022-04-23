#include "ChunkStatusEnum.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Enum::ChunkStatus>()
		{
			Reflect<Enum::ChunkStatus>::Enum
			(
				"ChunkLoaderShape",
				Value<Enum::ChunkStatus::Unloaded>("Unloaded"),
				Value<Enum::ChunkStatus::NotGenerated>("NotGenerated"),
				Value<Enum::ChunkStatus::Loading>("Loading"),
				Value<Enum::ChunkStatus::Loaded>("Loaded")
			);
		}
	}
}