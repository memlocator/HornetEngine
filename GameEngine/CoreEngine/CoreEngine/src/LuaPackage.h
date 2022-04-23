#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct LuaPackage {};

		template <>
		extern void ReflectPackage<LuaPackage>();
	}
}