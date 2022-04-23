#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct PhysicsPackage {};

		template <>
		extern void ReflectPackage<PhysicsPackage>();
	}
}