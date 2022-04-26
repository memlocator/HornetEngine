#include "Chunk.h"

#include "Camera.h"
#include "Terrain.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Chunk>()
		{
			Reflect<Chunk, Object>::Class
			(
				"Chunk",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Function(
					"Save",
					Overload(
						Const,
						Returns<void>()
					).Bind<Chunk, &Chunk::Save>()
				),

				Function(
					"Load",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<Chunk, &Chunk::Load>()
				),

				Function(
					"Regenerate",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<Chunk, &Chunk::Regenerate>()
				),

				Function(
					"Draw",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<bool>("drawLiquid"),
						Argument<const std::shared_ptr<GraphicsEngine::Camera>&>("targetCamera")
					).Bind<Chunk, &Chunk::Draw>()
				),

				Function(
					"GetCell",
					Overload(
						Const,
						Returns<CellData>(),
						Argument<const Coordinates&>("cell")
					).Bind<Chunk, &Chunk::GetCell>(),
					Overload(
						Const,
						Returns<CellData>(),
						Argument<const Vector3&>("cell")
					).Bind<Chunk, &Chunk::GetCell>()
				),

				Function(
					"GetCoordinates",
					Overload(
						Const,
						Returns<Coordinates>()
					).Bind<Chunk, &Chunk::GetCoordinates>()
				),

				Function(
					"GetMaterialID",
					Overload(
						Const,
						Returns<unsigned short>(),
						Argument<const Coordinates&>("cell")
					).Bind<Chunk, &Chunk::GetMaterialID>(),
					Overload(
						Const,
						Returns<unsigned short>(),
						Argument<const Vector3&>("cell")
					).Bind<Chunk, &Chunk::GetMaterialID>()
				),

				Function(
					"SetCell",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Coordinates&>("cell"),
						Argument<const CellData&>("data")
					).Bind<Chunk, &Chunk::SetCell>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Coordinates&>("cell"),
						Argument<float>("occupancy"),
						Argument<const std::shared_ptr<TerrainMaterial>&>("material"),
						Argument<const std::shared_ptr<Voxel>&>("voxel")
					).Bind<Chunk, &Chunk::SetCell>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("cell"),
						Argument<const CellData&>("data")
					).Bind<Chunk, &Chunk::SetCell>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("cell"),
						Argument<float>("occupancy"),
						Argument<const std::shared_ptr<TerrainMaterial>&>("material"),
						Argument<const std::shared_ptr<Voxel>&>("voxel")
					).Bind<Chunk, &Chunk::SetCell>()
				),

				Function(
					"SetOccupancy",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Coordinates&>("cell"),
						Argument<float>("occupancy")
					).Bind<Chunk, &Chunk::SetOccupancy>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("cell"),
						Argument<float>("occupancy")
					).Bind<Chunk, &Chunk::SetOccupancy>()
				),

				Function(
					"SetMaterial",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Coordinates&>("cell"),
						Argument<const std::shared_ptr<TerrainMaterial>&>("material")
					).Bind<Chunk, &Chunk::SetMaterial>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("cell"),
						Argument<const std::shared_ptr<TerrainMaterial>&>("material")
					).Bind<Chunk, &Chunk::SetMaterial>()
				),

				Function(
					"SetData",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Coordinates&>("cell"),
						Argument<const std::shared_ptr<Voxel>&>("data")
					).Bind<Chunk, &Chunk::SetData>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("cell"),
						Argument<const std::shared_ptr<Voxel>&>("data")
					).Bind<Chunk, &Chunk::SetData>()
				),

				Function(
					"Fetchchunk",
					Overload(
						Mutable,
						Returns<std::shared_ptr<Chunk>>(),
						Argument<int>("chunkX"),
						Argument<int>("chunkY"),
						Argument<int>("chunkZ")
					).Bind<Chunk, &Chunk::FetchChunk>()
				),

				Function(
					"GetTerrain",
					Overload(
						Const,
						Returns<std::shared_ptr<Terrain>>()
					).Bind<Chunk, &Chunk::GetTerrain>()
				)
			);
		}
	}
}