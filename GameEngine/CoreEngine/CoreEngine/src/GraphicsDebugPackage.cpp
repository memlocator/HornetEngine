#include "GraphicsDebugPackage.h"

#include "DebugDraw.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		extern void ReflectType<DebugDraw>();

		template <>
		void ReflectPackage<GraphicsDebugPackage>()
		{
			ReflectFromPackage<
				DebugDraw
			>();
		}
	}
}