#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct GraphicsScenePackage {};

		template <>
		extern void ReflectPackage<GraphicsScenePackage>();
	}
}