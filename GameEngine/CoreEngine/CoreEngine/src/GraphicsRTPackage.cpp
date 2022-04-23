#include "GraphicsRTPackage.h"

#include "RayTracer.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		extern void ReflectType<GraphicsEngine::RayTracer>();

		template <>
		void ReflectPackage<GraphicsRTPackage>()
		{
			ReflectFromPackage<
				GraphicsEngine::RayTracer
			>();
		}
	}
}