//#include "Matrix3.h"
#include "Reflection/Reflection.h"

#include "Matrix3.h"
#include "Vector2.h"
#include "Matrix4-decl.h"

namespace Engine
{
	namespace Reflection
	{
		template <typename Number>
		void ReflectMatrix3Type(const char* name, const char* alias)
		{
			std::vector<std::string> aliases;

			if (alias != nullptr)
				aliases.push_back(alias);

			Reflect<Matrix3Type<Number>>::Type(
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
						Argument<Number>("y")
					),
					Overload(
						Argument<const Vector2Type<Number, Number>&>("vector")
					),
					Overload(
						Argument<const Vector2Type<Number, Number>&>("position"),
						Argument<const Vector2Type<Number, Number>&>("right"),
						Argument<const Vector2Type<Number, Number>&>("up")
					),
					Overload(
						Argument<const Matrix3Type<float>&>("matrix")
					),
					Overload(
						Argument<const Matrix3Type<double>&>("matrix")
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
						Returns<Matrix3Type<Number>>()
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::Transposed>()
				),

				Function(
					"Inverted",
					Overload(
						Const,
						Returns<Matrix3Type<Number>>()
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::Inverted>()
				),

				Function(
					"Rotate",
					Overload(
						Mutable,
						Returns<Matrix3Type<Number>&>(),
						Argument<Number>("theta")
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::Rotate>()
				),

				Function(
					"Rotation",
					Overload(
						Const,
						Returns<Matrix3Type<Number>>(),
						Argument<const Vector2Type<Number, Number>&, Default(Vector2Type<Number, Number>())>("newTranslation")
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::Rotation>()
				),

				Function(
					"TransformedAround",
					Overload(
						Const,
						Returns<Matrix3Type<Number>>(),
						Argument<const Vector2Type<Number, Number>&>("point")
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::TransformedAround>()
				),

				Function(
					"RightVector",
					Overload(
						Const,
						Returns<Vector2Type<Number, Number>>()
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::RightVector>()
				),

				Function(
					"UpVector",
					Overload(
						Const,
						Returns<Vector2Type<Number, Number>>()
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::UpVector>()
				),

				Function(
					"Translation",
					Overload(
						Const,
						Returns<Vector2Type<Number, Number>>()
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::Translation>()
				),

				Function(
					"ExtractScale",
					Overload(
						Const,
						Returns<Vector2Type<Number, Number>>()
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::ExtractScale>()
				),

				Function(
					"Det",
					Overload(
						Const,
						Returns<Number>()
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::Det>()
				),

				Function(
					"operator+",
					Overload(
						Const,
						Returns<Matrix3Type<Number>>(),
						Argument<const Matrix3Type<Number>&>("other")
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::operator+>()
				),

				Function(
					"operator-",
					Overload(
						Const,
						Returns<Matrix3Type<Number>>(),
						Argument<const Matrix3Type<Number>&>("other")
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::operator- >(),
					Overload(
						Const,
						Returns<Matrix3Type<Number>>()
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::operator- >()
				),

				Function(
					"operator*",
					Overload(
						Const,
						Returns<Matrix3Type<Number>>(),
						Argument<const Matrix3Type<Number>&>("other")
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::operator*>(),
					Overload(
						Const,
						Returns<Matrix3Type<Number>>(),
						Argument<Number>("scalar")
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::operator*>(),
					Overload(
						Const,
						Returns<Vector2Type<Number, Number>>(),
						Argument<const Vector2Type<Number, Number>&>("vector")
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::operator*>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Matrix3Type<Number>, &Matrix3Type<Number>::operator std::string>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Matrix3Type<Number>&>("other")
					).Bind < Matrix3Type<Number>, &Matrix3Type<Number>::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Matrix3Type<Number>&>("other")
					).Bind < Matrix3Type<Number>, &Matrix3Type<Number>::operator!=>()
				),

				Function(
					"NewScale",
					Overload(
						Static,
						Returns<Matrix3Type<Number>>(),
						Argument<Number>("x"),
						Argument<Number>("y")
					).Bind<&Matrix3Type<Number>::NewScale>(),
					Overload(
						Static,
						Returns<Matrix3Type<Number>>(),
						Argument<const Vector2Type<Number, Number>&>("vector")
					).Bind<&Matrix3Type<Number>::NewScale>()
				),

				Function(
					"Rotation",
					Overload(
						Static,
						Returns<Matrix3Type<Number>>(),
						Argument<Number>("theta")
					).Bind<&Matrix3Type<Number>::Rotation>()
				)
			);
		}
		template <typename T>
		struct Matrix3TypeAlias
		{
			static inline bool ShouldAlias = false;
		};

		template <>
		struct Matrix3TypeAlias<Float>
		{
			static inline bool ShouldAlias = true;
		};

		template <>
		void ReflectType<Matrix3>()
		{
			ReflectMatrix3Type<float>("Matrix3F", Matrix3TypeAlias<float>::ShouldAlias ? "Matrix3" : nullptr);
			ReflectMatrix3Type<double>("Matrix3D", Matrix3TypeAlias<double>::ShouldAlias ? "Matrix3" : nullptr);
		}
	}
}