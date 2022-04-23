#include "Materials.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Materials>()
		{
			Reflect<Materials, Object>::Class
			(
				"Materials",
				{ "GameObject" }
			);
		}
	}
}