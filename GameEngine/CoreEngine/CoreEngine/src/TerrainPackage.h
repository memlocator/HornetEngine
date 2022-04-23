#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct TerrainPackage {};

		template <>
		extern void ReflectPackage<TerrainPackage>();
	}
}