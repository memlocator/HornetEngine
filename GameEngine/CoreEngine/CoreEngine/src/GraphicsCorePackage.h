#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct GraphicsCorePackage {};

		template <>
		extern void ReflectPackage<GraphicsCorePackage>();
	}
}