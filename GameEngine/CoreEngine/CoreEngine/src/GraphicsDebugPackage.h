#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct GraphicsDebugPackage {};

		template <>
		extern void ReflectPackage<GraphicsDebugPackage>();
	}
}