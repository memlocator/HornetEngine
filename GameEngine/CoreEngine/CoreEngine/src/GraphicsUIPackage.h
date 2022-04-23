#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct GraphicsUIPackage {};

		template <>
		extern void ReflectPackage<GraphicsUIPackage>();
	}
}