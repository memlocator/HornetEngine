#include "Environments.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Environments>()
		{
			Reflect<Environments, Object>::Class
			(
				"Environments",
				{ "GameObject" }
			);
		}
	}
}