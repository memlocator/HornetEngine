#include "Coordinates.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Coordinates>()
		{
			Reflect<Coordinates>::Type
			(
				"Coordinates",

				Member<Bind(&Coordinates::X)>("X"),
				Member<Bind(&Coordinates::Y)>("Y"),
				Member<Bind(&Coordinates::Z)>("Z"),

				Constructor(
					Overload(
						Argument<int, Default(0)>("x"),
						Argument<int, Default(0)>("y"),
						Argument<int, Default(0)>("z")
					),
					Overload(
						Argument<const Vector3&>("vector")
					)
				)
			);
		}
	}
}