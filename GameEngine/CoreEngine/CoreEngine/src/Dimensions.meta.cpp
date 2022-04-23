#include "Dimensions.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Dimensions>()
		{
			Reflect<Dimensions>::Type
			(
				"Dimensions",

				Member<Bind(&Dimensions::Width)>("Width"),
				Member<Bind(&Dimensions::Height)>("Height"),

				Constructor(
					Overload(
						Argument<unsigned int, Default(0)>("width"),
						Argument<unsigned int, Default(0)>("height")
					),
					Overload(
						Argument<const Vector3&>("size")
					)
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Dimensions, &Dimensions::operator std::string>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Dimensions&>("other")
					).Bind<Dimensions, &Dimensions::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Dimensions&>("other")
					).Bind<Dimensions, &Dimensions::operator!=>()
				)
			);
		}
	}
}