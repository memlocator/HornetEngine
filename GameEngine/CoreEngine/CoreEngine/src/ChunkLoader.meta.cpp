#include "ChunkLoader.h"

#include "Terrain.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<ChunkLoader>()
		{
			Reflect<ChunkLoader, Object>::Class
			(
				"ChunkLoader",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Member<Bind(&ChunkLoader::Shape)>("Shape"),
				Member<Bind(&ChunkLoader::Target)>("Target"),

				Function(
					"SetRange",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Coordinates&>("range")
					).Bind<ChunkLoader, &ChunkLoader::SetRange>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("range")
					).Bind<ChunkLoader, &ChunkLoader::SetRange>()
				),

				Function(
					"GetRange",
					Overload(
						Const,
						Returns<Coordinates>()
					).Bind<ChunkLoader, &ChunkLoader::GetRange>()
				),

				Function(
					"GetCellCoordinates",
					Overload(
						Const,
						Returns<Coordinates>()
					).Bind<ChunkLoader, &ChunkLoader::GetCellCoordinates>()
				),

				Function(
					"GetChunkCoordinates",
					Overload(
						Const,
						Returns<Coordinates>(),
						Argument<const Coordinates&, Default(Coordinates())>("chunk")
					).Bind<ChunkLoader, &ChunkLoader::GetChunkCoordinates>(),
					Overload(
						Const,
						Returns<Coordinates>(),
						Argument<const Vector3&>("chunk")
					).Bind<ChunkLoader, &ChunkLoader::GetChunkCoordinates>()
				),

				Function(
					"GetChunkStatus",
					Overload(
						Const,
						Returns<Enum::ChunkStatus>(),
						Argument<const Coordinates&, Default(Coordinates())>("chunk")
					).Bind<ChunkLoader, &ChunkLoader::GetChunkStatus>(),
					Overload(
						Const,
						Returns<Enum::ChunkStatus>(),
						Argument<const Vector3&>("chunk")
					).Bind<ChunkLoader, &ChunkLoader::GetChunkStatus>()
				),

				Function(
					"GetLocalChunkStatus",
					Overload(
						Const,
						Returns<Enum::ChunkStatus>(),
						Argument<const Coordinates&, Default(Coordinates())>("chunk")
					).Bind<ChunkLoader, &ChunkLoader::GetLocalChunkStatus>(),
					Overload(
						Const,
						Returns<Enum::ChunkStatus>(),
						Argument<const Vector3&>("chunk")
					).Bind<ChunkLoader, &ChunkLoader::GetLocalChunkStatus>()
				)
			);
		}
	}
}