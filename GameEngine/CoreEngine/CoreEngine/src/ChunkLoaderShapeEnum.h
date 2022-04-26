#pragma once

namespace EnumTypeStorage
{
	struct ChunkLoaderShapeEnum
	{
		enum ChunkLoaderShape
		{
			Box,
			Sphere,
			CylinderX,
			CylinderY,
			CylinderZ
		};
	};
}

namespace Enum
{
	typedef EnumTypeStorage::ChunkLoaderShapeEnum::ChunkLoaderShape ChunkLoaderShape;
}