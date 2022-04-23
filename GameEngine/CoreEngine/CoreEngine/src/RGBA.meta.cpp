#include "RGBA.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<RGBA>()
		{
			Reflect<RGBA>::Type(
				"RGBA",

				Member<Bind(&RGBA::R)>("R"),
				Member<Bind(&RGBA::G)>("G"),
				Member<Bind(&RGBA::B)>("B"),
				Member<Bind(&RGBA::A)>("A"),

				Constructor(
					Overload(),
					Overload(
						Argument<float>("r"),
						Argument<float>("g"),
						Argument<float>("b"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Vector3&>("vector")
					)
				),

				Function(
					"Lerp",
					Overload(
						Const,
						Returns<RGBA>(),
						Argument<const RGBA&>("end"),
						Argument<float>("t")
					).Bind<RGBA, &RGBA::Lerp>()
				),

				Function(
					"ARGB",
					Overload(
						Const,
						Returns<unsigned int>()
					).Bind<RGBA, &RGBA::ARGB>()
				),

				Function(
					"ABGR",
					Overload(
						Const,
						Returns<unsigned int>()
					).Bind<RGBA, &RGBA::ABGR>()
				),

				Function(
					"Integer",
					Overload(
						Const,
						Returns<unsigned int>()
					).Bind<RGBA, &RGBA::operator unsigned int>()
				),

				Function(
					"Vector",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<RGBA, &RGBA::operator Vector3>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<RGBA, &RGBA::operator std::string>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const RGBA&>("other")
					).Bind<RGBA, &RGBA::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const RGBA&>("other")
					).Bind < RGBA, &RGBA::operator!=>()
				)
			);
		}
	}
}