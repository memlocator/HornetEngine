#include "Terrain.h"

#include "TerrainMaterial.h"
#include "Chunk.h"
#include "Voxel.h"
#include "Camera.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Terrain>()
		{
			Reflect<Terrain, Object>::Class
			(
				"Terrain",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Member<Bind(&Terrain::DataDirectory)>("DataDirectory"),

				Function(
					"CanLoadChunk",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Coordinates&>("chunk")
					).Bind<Terrain, &Terrain::CanLoadChunk>(),
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Vector3&>("chunk")
					).Bind<Terrain, &Terrain::CanLoadChunk>()
				),

				Function(
					"LoadChunk",
					Overload(
						Mutable,
						Returns<std::shared_ptr<Chunk>>(),
						Argument<const Coordinates&>("chunk")
					).Bind<Terrain, &Terrain::LoadChunk>()
				),

				Function(
					"UnloadChunk",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Coordinates&>("chunk")
					).Bind<Terrain, &Terrain::UnloadChunk>()
				),

				Function(
					"GetMaterial",
					Overload(
						Const,
						Returns<std::shared_ptr<TerrainMaterial>>(),
						Argument<unsigned short>("id")
					).Bind<Terrain, &Terrain::GetMaterial>()
				),

				Function(
					"GetChunkPath",
					Overload(
						Const,
						Returns<std::string>(),
						Argument<const Coordinates&>("chunk")
					).Bind<Terrain, &Terrain::GetChunkPath>()
				),

				Function(
					"GetChunkStatus",
					Overload(
						Const,
						Returns<Enum::ChunkStatus>(),
						Argument<const Coordinates&>("chunk")
					).Bind<Terrain, &Terrain::GetChunkStatus>(),
					Overload(
						Const,
						Returns<Enum::ChunkStatus>(),
						Argument<const Vector3&>("chunk")
					).Bind<Terrain, &Terrain::GetChunkStatus>()
				),

				Function(
					"GetChunkCoordinates",
					Overload(
						Const,
						Returns<Coordinates>(),
						Argument<const Coordinates&>("cell")
					).Bind<Terrain, &Terrain::GetChunkCoordinates>(),
					Overload(
						Const,
						Returns<Coordinates>(),
						Argument<const Vector3&>("cell")
					).Bind<Terrain, &Terrain::GetChunkCoordinates>()
				),

				Function(
					"GetCellCoordinates",
					Overload(
						Const,
						Returns<Coordinates>(),
						Argument<const Coordinates&>("chunk")
					).Bind<Terrain, &Terrain::GetCellCoordinates>(),
					Overload(
						Const,
						Returns<Coordinates>(),
						Argument<const Vector3&>("chunk")
					).Bind<Terrain, &Terrain::GetCellCoordinates>()
				),

				Function(
					"SetCell",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Coordinates&>("cell"),
						Argument<const CellData&>("data")
					).Bind<Terrain, &Terrain::SetCell>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Coordinates&>("cell"),
						Argument<float>("occupancy"),
						Argument<const std::shared_ptr<TerrainMaterial>&>("material"),
						Argument<const std::shared_ptr<Voxel>&>("voxel")
					).Bind<Terrain, &Terrain::SetCell>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("cell"),
						Argument<const CellData&>("data")
					).Bind<Terrain, &Terrain::SetCell>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("cell"),
						Argument<float>("occupancy"),
						Argument<const std::shared_ptr<TerrainMaterial>&>("material"),
						Argument<const std::shared_ptr<Voxel>&>("voxel")
					).Bind<Terrain, &Terrain::SetCell>()
				),

				Function(
					"SetOccupancy",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Coordinates&>("chunk"),
						Argument<float>("occupancy")
					).Bind<Terrain, &Terrain::SetOccupancy>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("chunk"),
						Argument<float>("occupancy")
					).Bind<Terrain, &Terrain::SetOccupancy>()
				),

				Function(
					"SetMaterial",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Coordinates&>("chunk"),
						Argument<const std::shared_ptr<TerrainMaterial>&>("material")
					).Bind<Terrain, &Terrain::SetMaterial>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("chunk"),
						Argument<const std::shared_ptr<TerrainMaterial>&>("material")
					).Bind<Terrain, &Terrain::SetMaterial>()
				),

				Function(
					"SetData",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Coordinates&>("chunk"),
						Argument<const std::shared_ptr<Voxel>&>("data")
					).Bind<Terrain, &Terrain::SetData>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("chunk"),
						Argument<const std::shared_ptr<Voxel>&>("data")
					).Bind<Terrain, &Terrain::SetData>()
				),

				Function(
					"Draw",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<bool>("drawLiquid"),
						Argument<const std::shared_ptr<GraphicsEngine::Camera>&>("targetCamera")
					).Bind<Terrain, &Terrain::Draw>()
				),

				Function(
					"GetChunk",
					Overload(
						Const,
						Returns<std::shared_ptr<Chunk>>(),
						Argument<const Vector3&>("chunk")
					).Bind<Terrain, &Terrain::GetChunk>()
				),

				Function(
					"GetChunkFromCell",
					Overload(
						Const,
						Returns<std::shared_ptr<Chunk>>(),
						Argument<const Vector3&>("cell")
					).Bind<Terrain, &Terrain::GetChunkFromCell>()
				),

				Function(
					"GetCell",
					Overload(
						Const,
						Returns<CellData>(),
						Argument<const Vector3&>("cell")
					).Bind<Terrain, &Terrain::GetCell>()
				)
			);
		}
	}
}