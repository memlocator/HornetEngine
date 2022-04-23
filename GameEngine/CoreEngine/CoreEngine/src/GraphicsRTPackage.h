#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct GraphicsRTPackage {};

		template <>
		extern void ReflectPackage<GraphicsRTPackage>();
	}
}