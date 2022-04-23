#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct EnginePackage {};

		template <>
		extern void ReflectPackage<EnginePackage>();
	}
}