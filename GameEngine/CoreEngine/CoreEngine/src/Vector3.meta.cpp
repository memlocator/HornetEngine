#include "Vector3.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Vector3>()
		{
			Reflect<Vector3>::Type(
				"Vector3",

				Member<Bind(&Vector3::X)>("X"),
				Member<Bind(&Vector3::Y)>("Y"),
				Member<Bind(&Vector3::Z)>("Z"),
				Member<Bind(&Vector3::W)>("W"),

				Constructor(
					Overload()
				),

				Constructor(
					Overload(
						Argument<float, Default(0.0f)>("x"),
						Argument<float, Default(0.0f)>("y"),
						Argument<float, Default(0.0f)>("z"),
						Argument<float, Default(0.0f)>("w")
					)
				),

				Function(
					"Dot",
					Overload(
						Const,
						Returns<float>(),
						Argument<const Vector3&>("other")
					).Bind<Vector3, &Vector3::Dot>()
				),

				Function(
					"Cross",
					Overload(
						Const,
						Returns<Vector3>(),
						Argument<const Vector3&>("other")
					).Bind<Vector3, &Vector3::Cross>()
				),

				Function(
					"Unit",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Vector3, &Vector3::Unit>()
				),

				Function(
					"Length",
					Overload(
						Const,
						Returns<float>()
					).Bind<Vector3, &Vector3::Length>()
				),

				Function(
					"SquareLength",
					Overload(
						Const,
						Returns<float>()
					).Bind<Vector3, &Vector3::SquareLength>()
				),

				Function(
					"InvertedLength",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Vector3, &Vector3::InvertedLength>()
				),

				Function(
					"operator-",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Vector3, &Vector3::operator- >(),
					Overload(
						Const,
						Returns<Vector3>(),
						Argument<const Vector3&>("other")
					).Bind<Vector3, &Vector3::operator- >()
				),

				Function(
					"operator+",
					Overload(
						Const,
						Returns<Vector3>(),
						Argument<const Vector3&>("other")
					).Bind<Vector3, &Vector3::operator+>()
				),

				Function(
					"operator*",
					Overload(
						Const,
						Returns<Vector3>(),
						Argument<float>("scalar")
					).Bind<Vector3, &Vector3::operator*>(),
					Overload(
						Const,
						Returns<float>(),
						Argument<const Vector3&>("other")
					).Bind<Vector3, &Vector3::operator*>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Vector3&>("other")
					).Bind<Vector3, &Vector3::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Vector3&>("other")
					).Bind<Vector3, &Vector3::operator!=>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Vector3, &Vector3::operator std::string>()
				)
			);
		}
	}
}