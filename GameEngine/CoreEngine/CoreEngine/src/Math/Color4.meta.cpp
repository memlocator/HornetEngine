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

#include "../Reflection/Reflection.h"

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
						Argument<unsigned char>("r"),
						Argument<unsigned char>("g"),
						Argument<unsigned char>("b"),
						Argument<unsigned char, Default(255_b)>("a")
					),
					Overload(
						Argument<unsigned int>("color")
					),
					Overload(
						Argument<const Color1&>("color"),
						Argument<float, Default(0.0f)>("g"),
						Argument<float, Default(0.0f)>("b"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Color1I&>("color"),
						Argument<float, Default(0.0f)>("g"),
						Argument<float, Default(0.0f)>("b"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Color2&>("color"),
						Argument<float, Default(0.0f)>("b"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Color2I&>("color"),
						Argument<float, Default(0.0f)>("b"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Color3&>("color"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Color3I&>("color"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Color4&>("color")
					),
					Overload(
						Argument<const Color4I&>("color")
					),
					Overload(
						Argument<const Vector2F&>("vector"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Vector2D&>("vector"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Vector2I&>("vector"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Vector2SF&>("vector"),
						Argument<float, Default(0.0f)>("b"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Vector2SD&>("vector"),
						Argument<float, Default(0.0f)>("b"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Vector2SI&>("vector"),
						Argument<float, Default(0.0f)>("b"),
						Argument<float, Default(1.0f)>("a")
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
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Vector3SD&>("vector"),
						Argument<float, Default(1.0f)>("a")
					),
					Overload(
						Argument<const Vector3SI&>("vector"),
						Argument<float, Default(1.0f)>("a")
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
					).Bind<Color4, &Color4::operator!=>()
				)
			);
		}
	}
}