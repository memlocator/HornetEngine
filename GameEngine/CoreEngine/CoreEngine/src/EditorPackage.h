#pragma once

#include "Reflection/ReflectionPackage.h"

namespace Engine
{
	namespace Reflection
	{
		struct EditorPackage {};

		template <>
		extern void ReflectPackage<EditorPackage>();
	}
}