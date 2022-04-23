#include "Environment.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Environment>()
		{
			Reflect<Environment, Object>::Class
			(
				"Environment",
				{ "GameObject" }
			);
		}
	}
}