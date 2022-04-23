#include "Simulation.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Simulation>()
		{
			Reflect<Simulation, Object>::Class
			(
				"Simulation",
				{ "GameObject" }
			);
		}
	}
}