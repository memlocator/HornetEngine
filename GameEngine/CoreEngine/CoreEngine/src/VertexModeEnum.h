#pragma once

namespace EnumTypeStorage
{
	struct VertexModeEnum
	{
		enum VertexMode
		{
			Seperate,
			Shared,
			Smoothened,
			Wireframe
		};
	};
}

namespace Enum
{
	typedef EnumTypeStorage::VertexModeEnum::VertexMode VertexMode;
}