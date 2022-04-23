#include "TerrainPackage.h"

#include "ChunkLoaderShapeEnum.h"
#include "ChunkStatusEnum.h"
#include "CellData.h"
#include "Chunk.h"
#include "ChunkLoader.h"
#include "Coordinates.h"
#include "Terrain.h"
#include "Terrain2DCollider.h"
#include "TerrainMaterial.h"
#include "Voxel.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		extern void ReflectType<Enum::ChunkLoaderShape>();
		
		template <>
		extern void ReflectType<Enum::ChunkStatus>();
		
		template <>
		extern void ReflectType<CellData>();
		
		template <>
		extern void ReflectType<Chunk>();
		
		template <>
		extern void ReflectType<ChunkLoader>();
		
		template <>
		extern void ReflectType<Coordinates>();
		
		template <>
		extern void ReflectType<Terrain>();
		
		template <>
		extern void ReflectType<Terrain2DCollider>();
		
		template <>
		extern void ReflectType<TerrainMaterial>();
		
		template <>
		extern void ReflectType<Voxel>();

		template <>
		void ReflectPackage<TerrainPackage>()
		{
			ReflectFromPackage<
				Enum::ChunkLoaderShape,
				Enum::ChunkStatus,
				CellData,
				Chunk,
				ChunkLoader,
				Coordinates,
				Terrain,
				Terrain2DCollider,
				TerrainMaterial,
				Voxel
			>();
		}
	}
}