#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct GraphicsDataPackage {};

		template <>
		extern void ReflectPackage<GraphicsDataPackage>();
	}
}