#include "PointMass.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace Engine::Physics;

		template <>
		void ReflectType<PointMass>()
		{
			Reflect<PointMass, Object>::Class
			(
				"PointMass",
				{ "GameObject", "Physics" },

				Member<Bind(&PointMass::Mass)>("Mass"),
				Member<Bind(&PointMass::Position)>("Position"),

				Constructor(
					Overload()
				)
			);
		}
	}
}