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
		void ReflectType<Color1I>()
		{
			Reflect<Color1I>::Type(
				"Color1I",

				Member<Bind(&Color1I::R)>("R"),

				Constructor(
					Overload(),
					Overload(
						Argument<unsigned char>("r")
					),
					Overload(
						Argument<unsigned char>("r")
					),
					Overload(
						Argument<unsigned int>("color")
					),
					Overload(
						Argument<const Color1&>("color")
					),
					Overload(
						Argument<const Color1I&>("color")
					),
					Overload(
						Argument<const Color2&>("color")
					),
					Overload(
						Argument<const Color2I&>("color")
					),
					Overload(
						Argument<const Color3&>("color")
					),
					Overload(
						Argument<const Color3I&>("color")
					),
					Overload(
						Argument<const Color4&>("color")
					),
					Overload(
						Argument<const Color4I&>("color")
					),
					Overload(
						Argument<const Vector2F&>("vector")
					),
					Overload(
						Argument<const Vector2D&>("vector")
					),
					Overload(
						Argument<const Vector2I&>("vector")
					),
					Overload(
						Argument<const Vector2SF&>("vector")
					),
					Overload(
						Argument<const Vector2SD&>("vector")
					),
					Overload(
						Argument<const Vector2SI&>("vector")
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
						Argument<const Vector3SF&>("vector")
					),
					Overload(
						Argument<const Vector3SD&>("vector")
					),
					Overload(
						Argument<const Vector3SI&>("vector")
					)
				),

				Function(
					"Lerp",
					Overload(
						Const,
						Returns<Color1I>(),
						Argument<const Color1I&>("end"),
						Argument<float>("t")
					).Bind<Color1I, &Color1I::Lerp>()
				),

				Function(
					"ARGB",
					Overload(
						Const,
						Returns<unsigned int>()
					).Bind<Color1I, &Color1I::ARGB>()
				),

				Function(
					"ABGR",
					Overload(
						Const,
						Returns<unsigned int>()
					).Bind<Color1I, &Color1I::ABGR>()
				),

				Function(
					"Integer",
					Overload(
						Const,
						Returns<unsigned int>()
					).Bind<Color1I, &Color1I::operator unsigned int>()
				),

				Function(
					"Vector",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Color1I, &Color1I::operator Vector3>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Color1I, &Color1I::operator std::string>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Color1I&>("other")
					).Bind<Color1I, &Color1I::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Color1I&>("other")
					).Bind<Color1I, &Color1I::operator!=>()
				)
			);
		}
	}
}