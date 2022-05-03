#include "Matrix4.h"
#include "Vector3.h"
#include "Matrix3-decl.h"

#include "../Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <typename Number>
		void ReflectMatrix4Type(const char* name, const char* alias)
		{
			std::vector<std::string> aliases;

			if (alias != nullptr)
				aliases.push_back(alias);

			Reflect<Matrix4Type<Number>>::Type(
				name,
				{},
				aliases,

				Constructor(
					Overload(),
					Overload(
						Argument<bool>("noIdentity")
					),
					Overload(
						Argument<Number>("x"),
						Argument<Number>("y"),
						Argument<Number>("z")
					),
					Overload(
						Argument<const Vector3Type<Number, Number>&>("vector")
					),
					Overload(
						Argument<const Vector3Type<Number, Number>&>("position"),
						Argument<const Vector3Type<Number, Number>&>("right"),
						Argument<const Vector3Type<Number, Number>&>("up"),
						Argument<const Vector3Type<Number, Number>&>("front")
					),
					Overload(
						Argument<const Matrix3Type<float>&>("matrix"),
						Argument<const Vector3Type<Number, Number>&>("translation")
					),
					Overload(
						Argument<const Matrix3Type<double>&>("matrix"),
						Argument<const Vector3Type<Number, Number>&>("translation")
					),
					Overload(
						Argument<const Matrix4Type<float>&>("matrix")
					),
					Overload(
						Argument<const Matrix4Type<double>&>("matrix")
					)
				),

				Function(
					"Transposed",
					Overload(
						Const,
						Returns<Matrix4Type<Number>>()
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::Transposed>()
				),

				Function(
					"Inverted",
					Overload(
						Const,
						Returns<Matrix4Type<Number>>()
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::Inverted>()
				),

				Function(
					"Rotation",
					Overload(
						Const,
						Returns<Matrix4Type<Number>>(),
						Argument<const Vector3Type<Number, Number>&, Default(Vector3Type<Number, Number>())>("newTranslation")
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::Rotation>()
				),

				Function(
					"TransformedAround",
					Overload(
						Const,
						Returns<Matrix4Type<Number>>(),
						Argument<const Vector3Type<Number, Number>&>("point")
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::TransformedAround>()
				),

				Function(
					"RightVector",
					Overload(
						Const,
						Returns<Vector3Type<Number, Number>>()
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::RightVector>()
				),

				Function(
					"UpVector",
					Overload(
						Const,
						Returns<Vector3Type<Number, Number>>()
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::UpVector>()
				),

				Function(
					"FrontVector",
					Overload(
						Const,
						Returns<Vector3Type<Number, Number>>()
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::FrontVector>()
				),

				Function(
					"Translation",
					Overload(
						Const,
						Returns<Vector3Type<Number, Number>>()
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::Translation>()
				),

				Function(
					"ExtractScale",
					Overload(
						Const,
						Returns<Vector3Type<Number, Number>>()
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::ExtractScale>()
				),

				Function(
					"Det",
					Overload(
						Const,
						Returns<Number>()
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::Det>()
				),

				Function(
					"operator+",
					Overload(
						Const,
						Returns<Matrix4Type<Number>>(),
						Argument<const Matrix4Type<Number>&>("other")
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::operator+>()
				),

				Function(
					"operator-",
					Overload(
						Const,
						Returns<Matrix4Type<Number>>(),
						Argument<const Matrix4Type<Number>&>("other")
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::operator- >(),
					Overload(
						Const,
						Returns<Matrix4Type<Number>>()
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::operator- >()
				),

				Function(
					"operator*",
					Overload(
						Const,
						Returns<Matrix4Type<Number>>(),
						Argument<const Matrix4Type<Number>&>("other")
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::operator*>(),
					Overload(
						Const,
						Returns<Matrix4Type<Number>>(),
						Argument<Number>("scalar")
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::operator*>(),
					Overload(
						Const,
						Returns<Vector3Type<Number, Number>>(),
						Argument<const Vector3Type<Number, Number>&>("vector")
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::operator*>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::operator std::string>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Matrix4Type<Number>&>("other")
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Matrix4Type<Number>&>("other")
					).Bind<Matrix4Type<Number>, &Matrix4Type<Number>::operator!=>()
				),

				Function(
					"NewScale",
					Overload(
						Static,
						Returns<Matrix4Type<Number>>(),
						Argument<Number>("x"),
						Argument<Number>("y"),
						Argument<Number>("z")
					).Bind<&Matrix4Type<Number>::NewScale>(),
					Overload(
						Static,
						Returns<Matrix4Type<Number>>(),
						Argument<const Vector3Type<Number, Number>&>("vector")
					).Bind<&Matrix4Type<Number>::NewScale>()
				),

				Function(
					"AxisRotation",
					Overload(
						Static,
						Returns<Matrix4Type<Number>>(),
						Argument<const Vector3Type<Number, Number>&>("axis"),
						Argument<Number>("theta")
					).Bind<&Matrix4Type<Number>::AxisRotation>()
				),

				Function(
					"PitchRotation",
					Overload(
						Static,
						Returns<Matrix4Type<Number>>(),
						Argument<Number>("theta")
					).Bind<&Matrix4Type<Number>::PitchRotation>()
				),

				Function(
					"YawRotation",
					Overload(
						Static,
						Returns<Matrix4Type<Number>>(),
						Argument<Number>("theta")
					).Bind<&Matrix4Type<Number>::YawRotation>()
				),

				Function(
					"RollRotation",
					Overload(
						Static,
						Returns<Matrix4Type<Number>>(),
						Argument<Number>("theta")
					).Bind<&Matrix4Type<Number>::RollRotation>()
				),

				Function(
					"EulerAnglesRotation",
					Overload(
						Static,
						Returns<Matrix4Type<Number>>(),
						Argument<Number>("pitch"),
						Argument<Number>("yaw"),
						Argument<Number>("roll")
					).Bind<&Matrix4Type<Number>::EulerAnglesRotation>()
				),

				Function(
					"EulerAnglesYawRotation",
					Overload(
						Static,
						Returns<Matrix4Type<Number>>(),
						Argument<Number>("yaw"),
						Argument<Number>("pitch"),
						Argument<Number>("roll")
					).Bind<&Matrix4Type<Number>::EulerAnglesYawRotation>()
				),

				Function(
					"NewProjection",
					Overload(
						Static,
						Returns<Matrix4Type<Number>>(),
						Argument<Number>("distance"),
						Argument<Number>("nearPlane"),
						Argument<Number>("farPlane"),
						Argument<Number>("width"),
						Argument<Number>("height")
					).Bind<&Matrix4Type<Number>::NewProjection>()
				),

				Function(
					"Facing",
					Overload(
						Static,
						Returns<Matrix4Type<Number>>(),
						Argument<const Vector3Type<Number, Number>&>("position"),
						Argument<const Vector3Type<Number, Number>&>("direction"),
						Argument<const Vector3Type<Number, Number>&, Default(Vector3Type<Number, Number>(0, 1, 0))>("globalUp")
					).Bind<&Matrix4Type<Number>::Facing>()
				)
			);
		}
		template <typename T>
		struct Matrix4TypeAlias
		{
			static inline bool ShouldAlias = false;
		};

		template <>
		struct Matrix4TypeAlias<Float>
		{
			static inline bool ShouldAlias = true;
		};

		template <>
		void ReflectType<Matrix4>()
		{
			ReflectMatrix4Type<float>("Matrix4F", Matrix4TypeAlias<float>::ShouldAlias ? "Matrix4" : nullptr);
			ReflectMatrix4Type<double>("Matrix4D", Matrix4TypeAlias<double>::ShouldAlias ? "Matrix4" : nullptr);
		}
	}
}