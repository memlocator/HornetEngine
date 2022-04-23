#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct GraphicsOperationPackage {};

		template <>
		extern void ReflectPackage<GraphicsOperationPackage>();
	}
}