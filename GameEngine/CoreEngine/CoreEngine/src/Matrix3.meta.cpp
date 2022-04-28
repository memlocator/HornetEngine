#include "Matrix3.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Matrix3>()
		{
			Reflect<Matrix3>::Type(
				"Matrix3",

				Constructor(
					Overload(),
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
						Returns<Matrix3>()
					).Bind<Matrix3, &Matrix3::Transposed>()
				),

				Function(
					"Inverted",
					Overload(
						Const,
						Returns<Matrix3>()
					).Bind<Matrix3, &Matrix3::Inverted>()
				),

				Function(
					"Rotation",
					Overload(
						Const,
						Returns<Matrix3>(),
						Argument<const Vector3&, Default(Vector3())>("newTranslation")
					).Bind<Matrix3, &Matrix3::Rotation>()
				),

				Function(
					"TransformedAround",
					Overload(
						Const,
						Returns<Matrix3>(),
						Argument<const Vector3&>("point")
					).Bind<Matrix3, &Matrix3::TransformedAround>()
				),

				Function(
					"RightVector",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Matrix3, &Matrix3::RightVector>()
				),

				Function(
					"UpVector",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Matrix3, &Matrix3::UpVector>()
				),

				Function(
					"FrontVector",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Matrix3, &Matrix3::FrontVector>()
				),

				Function(
					"Translation",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Matrix3, &Matrix3::Translation>()
				),

				Function(
					"ExtractScale",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Matrix3, &Matrix3::ExtractScale>()
				),

				Function(
					"Det",
					Overload(
						Const,
						Returns<Float>()
					).Bind<Matrix3, &Matrix3::Det>()
				),

				Function(
					"operator+",
					Overload(
						Const,
						Returns<Matrix3>(),
						Argument<const Matrix3&>("other")
					).Bind<Matrix3, &Matrix3::operator+>()
				),

				Function(
					"operator-",
					Overload(
						Const,
						Returns<Matrix3>(),
						Argument<const Matrix3&>("other")
					).Bind<Matrix3, &Matrix3::operator- >(),
					Overload(
						Const,
						Returns<Matrix3>()
					).Bind<Matrix3, &Matrix3::operator- >()
				),

				Function(
					"operator*",
					Overload(
						Const,
						Returns<Matrix3>(),
						Argument<const Matrix3&>("other")
					).Bind<Matrix3, &Matrix3::operator*>(),
					Overload(
						Const,
						Returns<Matrix3>(),
						Argument<Float>("scalar")
					).Bind<Matrix3, &Matrix3::operator*>(),
					Overload(
						Const,
						Returns<Vector3>(),
						Argument<const Vector3&>("vector")
					).Bind<Matrix3, &Matrix3::operator*>()
				),

				Function(
					"FullMultiply",
					Overload(
						Const,
						Returns<Matrix3>(),
						Argument<const Matrix3&>("other")
					).Bind<Matrix3, &Matrix3::FullMultiply>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Matrix3, &Matrix3::operator std::string>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Matrix3&>("other")
					).Bind<Matrix3, &Matrix3::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Matrix3&>("other")
					).Bind<Matrix3, &Matrix3::operator!=>()
				),

				Function(
					"NewScale",
					Overload(
						Static,
						Returns<Matrix3>(),
						Argument<Float>("x"),
						Argument<Float>("y"),
						Argument<Float>("z")
					).Bind<&Matrix3::NewScale>(),
					Overload(
						Static,
						Returns<Matrix3>(),
						Argument<const Vector3&>("vector")
					).Bind<&Matrix3::NewScale>()
				),

				Function(
					"AxisRotation",
					Overload(
						Static,
						Returns<Matrix3>(),
						Argument<const Vector3&>("axis"),
						Argument<Float>("theta")
					).Bind<&Matrix3::AxisRotation>()
				),

				Function(
					"PitchRotation",
					Overload(
						Static,
						Returns<Matrix3>(),
						Argument<Float>("theta")
					).Bind<&Matrix3::PitchRotation>()
				),

				Function(
					"YawRotation",
					Overload(
						Static,
						Returns<Matrix3>(),
						Argument<Float>("theta")
					).Bind<&Matrix3::YawRotation>()
				),

				Function(
					"RollRotation",
					Overload(
						Static,
						Returns<Matrix3>(),
						Argument<Float>("theta")
					).Bind<&Matrix3::RollRotation>()
				),

				Function(
					"EulerAnglesRotation",
					Overload(
						Static,
						Returns<Matrix3>(),
						Argument<Float>("pitch"),
						Argument<Float>("yaw"),
						Argument<Float>("roll")
					).Bind<&Matrix3::EulerAnglesRotation>()
				),

				Function(
					"EulerAnglesYawRotation",
					Overload(
						Static,
						Returns<Matrix3>(),
						Argument<Float>("yaw"),
						Argument<Float>("pitch"),
						Argument<Float>("roll")
					).Bind<&Matrix3::EulerAnglesYawRotation>()
				),

				Function(
					"NewProjection",
					Overload(
						Static,
						Returns<Matrix3>(),
						Argument<Float>("distance"),
						Argument<Float>("nearPlane"),
						Argument<Float>("farPlane"),
						Argument<Float>("width"),
						Argument<Float>("height")
					).Bind<&Matrix3::NewProjection>()
				),

				Function(
					"Facing",
					Overload(
						Static,
						Returns<Matrix3>(),
						Argument<const Vector3&>("position"),
						Argument<const Vector3&>("direction"),
						Argument<const Vector3&, Default(Vector3(0, 1, 0))>("globalUp")
					).Bind<&Matrix3::Facing>()
				)
			);
		}
	}
}