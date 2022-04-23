#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct NetworkingPackage {};

		template <>
		extern void ReflectPackage<NetworkingPackage>();
	}
}