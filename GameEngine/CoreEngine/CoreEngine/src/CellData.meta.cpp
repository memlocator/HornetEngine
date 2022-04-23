#include "CellData.h"

#include "TerrainMaterial.h"
#include "Voxel.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<CellData>()
		{
			Reflect<CellData>::Type
			(
				"CellData",
				{ "GameObject" },

				Member<Bind(&CellData::Occupancy)>("Occupancy"),
				Member<Bind(&CellData::MaterialType)>("MaterialType"),
				Member<Bind(&CellData::VoxelData)>("VoxelData"),

				Constructor(
					Overload(),
					Overload(
						Argument<float>("occupancy"),
						Argument<const std::shared_ptr<TerrainMaterial>&>("material"),
						Argument<const std::shared_ptr<Voxel>&>("voxel")
					)
				)
			);
		}
	}
}