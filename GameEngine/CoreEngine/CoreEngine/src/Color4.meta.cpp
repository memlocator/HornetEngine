#include "Color4.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Color4>()
		{
			Reflect<Color4>::Type(
				"Color4",

				Member<Bind(&Color4::R)>("R"),
				Member<Bind(&Color4::G)>("G"),
				Member<Bind(&Color4::B)>("B"),
				Member<Bind(&Color4::A)>("A"),

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
						Returns<Color4>(),
						Argument<const Color4&>("end"),
						Argument<float>("t")
					).Bind<Color4, &Color4::Lerp>()
				),

				Function(
					"ARGB",
					Overload(
						Const,
						Returns<unsigned int>()
					).Bind<Color4, &Color4::ARGB>()
				),

				Function(
					"ABGR",
					Overload(
						Const,
						Returns<unsigned int>()
					).Bind<Color4, &Color4::ABGR>()
				),

				Function(
					"Integer",
					Overload(
						Const,
						Returns<unsigned int>()
					).Bind<Color4, &Color4::operator unsigned int>()
				),

				Function(
					"Vector",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Color4, &Color4::operator Vector3>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Color4, &Color4::operator std::string>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Color4&>("other")
					).Bind<Color4, &Color4::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Color4&>("other")
					).Bind < Color4, &Color4::operator!=>()
				)
			);
		}
	}
}