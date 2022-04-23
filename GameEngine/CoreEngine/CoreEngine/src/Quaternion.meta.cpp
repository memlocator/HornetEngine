#include "Quaternion.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Quaternion>()
		{
			Reflect<Quaternion>::Type(
				"Quaternion",

				Member<Bind(&Quaternion::X)>("X"),
				Member<Bind(&Quaternion::Y)>("Y"),
				Member<Bind(&Quaternion::Z)>("Z"),
				Member<Bind(&Quaternion::W)>("W"),

				Constructor(
					Overload(
						Argument<float, Default(0)>("w"),
						Argument<float, Default(0)>("x"),
						Argument<float, Default(0)>("y"),
						Argument<float, Default(0)>("z")
					),

					Overload(
						Argument<const Vector3&>("vector")
					),

					Overload(
						Argument<const Vector3&>("axis"),
						Argument<float>("angle")
					),

					Overload(
						Argument<float>("w"),
						Argument<const Vector3&>("vector")
					),
					Overload(
						Argument<const Matrix3&>("matrix")
					)
				),

				Function(
					"Inverse",
					Overload(
						Const,
						Returns<Quaternion>()
					).Bind<Quaternion, &Quaternion::Inverse>()
				),

				Function(
					"Slerp",
					Overload(
						Const,
						Returns<Quaternion>(),
						Argument<const Quaternion&>("destination"),
						Argument<float>("t")
					).Bind<Quaternion, &Quaternion::Slerp>()
				),

				Function(
					"operator*",
					Overload(
						Const,
						Returns<Quaternion>(),
						Argument<const Quaternion&>("other")
					).Bind<Quaternion, &Quaternion::operator*>()
				),

				Function(
					"Matrix",
					Overload(
						Const,
						Returns<Matrix3>()
					).Bind<Quaternion, &Quaternion::Matrix>()
				),

				Function(
					"Cross",
					Overload(
						Const,
						Returns<Quaternion>(),
						Argument<const Quaternion&>("other")
					).Bind<Quaternion, &Quaternion::Cross>()
				),

				Function(
					"Unit",
					Overload(
						Const,
						Returns<Quaternion>()
					).Bind<Quaternion, &Quaternion::Unit>()
				),

				Function(
					"Length",
					Overload(
						Const,
						Returns<float>()
					).Bind<Quaternion, &Quaternion::Length>()
				),

				Function(
					"SquareLength",
					Overload(
						Const,
						Returns<float>()
					).Bind<Quaternion, &Quaternion::SquareLength>()
				),

				Function(
					"Dot",
					Overload(
						Const,
						Returns<float>(),
						Argument<const Quaternion&>("other")
					).Bind<Quaternion, &Quaternion::Dot>()
				),

				Function(
					"operator-",
					Overload(
						Const,
						Returns<Quaternion>()
					).Bind<Quaternion, &Quaternion::operator- >(),
					Overload(
						Const,
						Returns<Quaternion>(),
						Argument<const Quaternion&>("other")
					).Bind<Quaternion, &Quaternion::operator- >()
				),

				Function(
					"operator+",
					Overload(
						Const,
						Returns<Quaternion>(),
						Argument<const Quaternion&>("other")
					).Bind<Quaternion, &Quaternion::operator+>()
				),

				Function(
					"operator*",
					Overload(
						Const,
						Returns<Quaternion>(),
						Argument<const Quaternion&>("other")
					).Bind<Quaternion, &Quaternion::operator*>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Quaternion&>("other")
					).Bind<Quaternion, &Quaternion::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Quaternion&>("other")
					).Bind<Quaternion, &Quaternion::operator!=>()
				),

				Function(
					"Vector",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Quaternion, &Quaternion::operator Vector3>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Quaternion, &Quaternion::operator std::string>()
				)
			);
		}
	}
}