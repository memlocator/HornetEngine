#include "Ray.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Ray>()
		{
			Reflect<Ray>::Type(
				"Ray",

				Member<Bind(&Ray::Start)>("Start"),
				Member<Bind(&Ray::Direction)>("Direction"),

				Constructor(
					Overload(),
					Overload(
						Argument<const Vector3&>("start"),
						Argument<const Vector3&>("direction")
					)
				)
			);
		}
	}
}