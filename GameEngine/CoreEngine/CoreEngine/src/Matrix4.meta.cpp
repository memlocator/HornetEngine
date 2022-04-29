#include "Matrix4.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Matrix4>()
		{
			Reflect<Matrix4>::Type(
				"Matrix4",

				Constructor(
					Overload(),
					Overload(
						Argument<bool>("noIdentity")
					),
					Overload(
						Argument<Float>("x"),
						Argument<Float>("y"),
						Argument<Float>("z")
					),
					Overload(
						Argument<const Vector3&>("vector")
					),
					Overload(
						Argument<const Vector3&>("position"),
						Argument<const Vector3&>("right"),
						Argument<const Vector3&>("up"),
						Argument<const Vector3&>("front")
					)
				),

				Function(
					"Transposed",
					Overload(
						Const,
						Returns<Matrix4>()
					).Bind<Matrix4, &Matrix4::Transposed>()
				),

				Function(
					"Inverted",
					Overload(
						Const,
						Returns<Matrix4>()
					).Bind<Matrix4, &Matrix4::Inverted>()
				),

				Function(
					"Rotation",
					Overload(
						Const,
						Returns<Matrix4>(),
						Argument<const Vector3&, Default(Vector3())>("newTranslation")
					).Bind<Matrix4, &Matrix4::Rotation>()
				),

				Function(
					"TransformedAround",
					Overload(
						Const,
						Returns<Matrix4>(),
						Argument<const Vector3&>("point")
					).Bind<Matrix4, &Matrix4::TransformedAround>()
				),

				Function(
					"RightVector",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Matrix4, &Matrix4::RightVector>()
				),

				Function(
					"UpVector",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Matrix4, &Matrix4::UpVector>()
				),

				Function(
					"FrontVector",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Matrix4, &Matrix4::FrontVector>()
				),

				Function(
					"Translation",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Matrix4, &Matrix4::Translation>()
				),

				Function(
					"ExtractScale",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Matrix4, &Matrix4::ExtractScale>()
				),

				Function(
					"Det",
					Overload(
						Const,
						Returns<Float>()
					).Bind<Matrix4, &Matrix4::Det>()
				),

				Function(
					"operator+",
					Overload(
						Const,
						Returns<Matrix4>(),
						Argument<const Matrix4&>("other")
					).Bind<Matrix4, &Matrix4::operator+>()
				),

				Function(
					"operator-",
					Overload(
						Const,
						Returns<Matrix4>(),
						Argument<const Matrix4&>("other")
					).Bind<Matrix4, &Matrix4::operator- >(),
					Overload(
						Const,
						Returns<Matrix4>()
					).Bind<Matrix4, &Matrix4::operator- >()
				),

				Function(
					"operator*",
					Overload(
						Const,
						Returns<Matrix4>(),
						Argument<const Matrix4&>("other")
					).Bind<Matrix4, &Matrix4::operator*>(),
					Overload(
						Const,
						Returns<Matrix4>(),
						Argument<Float>("scalar")
					).Bind<Matrix4, &Matrix4::operator*>(),
					Overload(
						Const,
						Returns<Vector3>(),
						Argument<const Vector3&>("vector")
					).Bind<Matrix4, &Matrix4::operator*>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Matrix4, &Matrix4::operator std::string>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Matrix4&>("other")
					).Bind<Matrix4, &Matrix4::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Matrix4&>("other")
					).Bind<Matrix4, &Matrix4::operator!=>()
				),

				Function(
					"NewScale",
					Overload(
						Static,
						Returns<Matrix4>(),
						Argument<Float>("x"),
						Argument<Float>("y"),
						Argument<Float>("z")
					).Bind<&Matrix4::NewScale>(),
					Overload(
						Static,
						Returns<Matrix4>(),
						Argument<const Vector3&>("vector")
					).Bind<&Matrix4::NewScale>()
				),

				Function(
					"AxisRotation",
					Overload(
						Static,
						Returns<Matrix4>(),
						Argument<const Vector3&>("axis"),
						Argument<Float>("theta")
					).Bind<&Matrix4::AxisRotation>()
				),

				Function(
					"PitchRotation",
					Overload(
						Static,
						Returns<Matrix4>(),
						Argument<Float>("theta")
					).Bind<&Matrix4::PitchRotation>()
				),

				Function(
					"YawRotation",
					Overload(
						Static,
						Returns<Matrix4>(),
						Argument<Float>("theta")
					).Bind<&Matrix4::YawRotation>()
				),

				Function(
					"RollRotation",
					Overload(
						Static,
						Returns<Matrix4>(),
						Argument<Float>("theta")
					).Bind<&Matrix4::RollRotation>()
				),

				Function(
					"EulerAnglesRotation",
					Overload(
						Static,
						Returns<Matrix4>(),
						Argument<Float>("pitch"),
						Argument<Float>("yaw"),
						Argument<Float>("roll")
					).Bind<&Matrix4::EulerAnglesRotation>()
				),

				Function(
					"EulerAnglesYawRotation",
					Overload(
						Static,
						Returns<Matrix4>(),
						Argument<Float>("yaw"),
						Argument<Float>("pitch"),
						Argument<Float>("roll")
					).Bind<&Matrix4::EulerAnglesYawRotation>()
				),

				Function(
					"NewProjection",
					Overload(
						Static,
						Returns<Matrix4>(),
						Argument<Float>("distance"),
						Argument<Float>("nearPlane"),
						Argument<Float>("farPlane"),
						Argument<Float>("width"),
						Argument<Float>("height")
					).Bind<&Matrix4::NewProjection>()
				),

				Function(
					"Facing",
					Overload(
						Static,
						Returns<Matrix4>(),
						Argument<const Vector3&>("position"),
						Argument<const Vector3&>("direction"),
						Argument<const Vector3&, Default(Vector3(0, 1, 0))>("globalUp")
					).Bind<&Matrix4::Facing>()
				)
			);
		}
	}
}