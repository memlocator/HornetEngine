#pragma once

namespace EnumTypeStorage
{
	struct TerrainColliderAxisEnum
	{
		enum TerrainColliderAxis
		{
			XYPlane,
			XZPlane,
			ZYPlane,

			YXPlane,
			ZXPlane,
			YZPlane
		};
	};
}

namespace Enum
{
	typedef EnumTypeStorage::TerrainColliderAxisEnum::TerrainColliderAxis TerrainColliderAxis;
}