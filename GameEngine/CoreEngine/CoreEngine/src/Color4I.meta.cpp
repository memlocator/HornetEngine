#include "Color1.h"
#include "Color1I.h"
#include "Color2.h"
#include "Color2I.h"
#include "Color3.h"
#include "Color3I.h"
#include "Color4.h"
#include "Color4I.h"
#include "Vector2-decl.h"
#include "Vector2S-decl.h"
#include "Vector3-decl.h"
#include "Vector3S-decl.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Color4I>()
		{
			Reflect<Color4I>::Type(
				"Color4I",

				Member<Bind(&Color4I::R)>("R"),
				Member<Bind(&Color4I::G)>("G"),
				Member<Bind(&Color4I::B)>("B"),
				Member<Bind(&Color4I::A)>("A"),

				Constructor(
					Overload(),
					Overload(
						Argument<unsigned char>("r"),
						Argument<unsigned char>("g"),
						Argument<unsigned char>("b"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<float>("r"),
						Argument<float>("g"),
						Argument<float>("b"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<unsigned int>("color")
					),
					Overload(
						Argument<const Color1&>("color"),
						Argument<unsigned char, Default(0_b)>("g"),
						Argument<unsigned char, Default(0_b)>("b"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Color1I&>("color"),
						Argument<unsigned char, Default(0_b)>("g"),
						Argument<unsigned char, Default(0_b)>("b"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Color2&>("color"),
						Argument<unsigned char, Default(0_b)>("b"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Color2I&>("color"),
						Argument<unsigned char, Default(0_b)>("b"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Color3&>("color"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Color3I&>("color"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Color4&>("color")
					),
					Overload(
						Argument<const Color4I&>("color")
					),
					Overload(
						Argument<const Vector2F&>("vector"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Vector2D&>("vector"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Vector2I&>("vector"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Vector2SF&>("vector"),
						Argument<unsigned char, Default(0_b)>("b"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Vector2SD&>("vector"),
						Argument<unsigned char, Default(0_b)>("b"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Vector2SI&>("vector"),
						Argument<unsigned char, Default(0_b)>("b"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Vector3F&>("vector")
					),
					Overload(
						Argument<const Vector3D&>("vector")
					),
					Overload(
						Argument<const Vector3I&>("vector")
					),
					Overload(
						Argument<const Vector3SF&>("vector"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Vector3SD&>("vector"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<const Vector3SI&>("vector"),
						Argument<unsigned char, Default(255_b)>("a")
					)
				),

				Function(
					"Lerp",
					Overload(
						Const,
						Returns<Color4I>(),
						Argument<const Color4I&>("end"),
						Argument<float>("t")
					).Bind<Color4I, &Color4I::Lerp>()
				),

				Function(
					"ARGB",
					Overload(
						Const,
						Returns<unsigned int>()
					).Bind<Color4I, &Color4I::ARGB>()
				),

				Function(
					"ABGR",
					Overload(
						Const,
						Returns<unsigned int>()
					).Bind<Color4I, &Color4I::ABGR>()
				),

				Function(
					"Integer",
					Overload(
						Const,
						Returns<unsigned int>()
					).Bind<Color4I, &Color4I::operator unsigned int>()
				),

				Function(
					"Vector",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Color4I, &Color4I::operator Vector3>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Color4I, &Color4I::operator std::string>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Color4I&>("other")
					).Bind<Color4I, &Color4I::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Color4I&>("other")
					).Bind<Color4I, &Color4I::operator!=>()
				)
			);
		}
	}
}