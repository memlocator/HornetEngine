#pragma once

namespace GraphicsEngine
{
	struct AlignmentEnum
	{
		enum Alignment
		{
			Minimum,
			Center,
			Maximum
		};
	};
}

namespace Enum
{
	typedef GraphicsEngine::AlignmentEnum::Alignment Alignment;
}