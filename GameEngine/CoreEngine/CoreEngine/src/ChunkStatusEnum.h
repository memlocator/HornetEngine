#pragma once

namespace EnumTypeStorage
{
	struct ChunkStatusEnum
	{
		enum ChunkStatus
		{
			Unloaded,
			NotGenerated,
			Loading,
			Loaded
		};
	};
}

namespace Enum
{
	typedef EnumTypeStorage::ChunkStatusEnum::ChunkStatus ChunkStatus;
}