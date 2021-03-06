#include "Vector2.h"

#include "Vector2-decl.h"
#include "Vector2S-decl.h"
#include "Vector3-decl.h"
#include "Vector3S-decl.h"

#include "../Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <typename Vector, typename Number, typename DistanceType, typename... Allowed>
		void ReflectVector2(const char* name, const char* alias)
		{
			std::vector<std::string> aliases;

			if (alias != nullptr)
				aliases.push_back(alias);

			Reflect<Vector, void, Allowed...>::Type(
				name,
				{},
				aliases,

				Member<Bind(&Vector::X)>("X"),
				Member<Bind(&Vector::Y)>("Y"),
				Member<Bind(&Vector::Z)>("Z"),

				Constructor(
					Overload(
						Argument<Number, Default((Number)0.0)>("x"),
						Argument<Number, Default((Number)0.0)>("y"),
						Argument<Number, Default((Number)0.0)>("z")
					),
					Overload(
						Argument<const Vector2Type<float, float>&>("vector")
					),
					Overload(
						Argument<const Vector2Type<double, double>&>("vector")
					),
					Overload(
						Argument<const Vector2Type<int, float>&>("vector")
					),
					Overload(
						Argument<const Vector2SType<float, float>&>("vector"),
						Argument<Number>("z")
					),
					Overload(
						Argument<const Vector2SType<double, double>&>("vector"),
						Argument<Number>("z")
					),
					Overload(
						Argument<const Vector2SType<int, float>&>("vector"),
						Argument<Number>("z")
					),
					Overload(
						Argument<const Vector3Type<float, float>&>("vector")
					),
					Overload(
						Argument<const Vector3Type<double, double>&>("vector")
					),
					Overload(
						Argument<const Vector3Type<int, float>&>("vector")
					),
					Overload(
						Argument<const Vector3SType<float, float>&>("vector")
					),
					Overload(
						Argument<const Vector3SType<double, double>&>("vector")
					),
					Overload(
						Argument<const Vector3SType<int, float>&>("vector")
					)
				),

				Function(
					"Dot",
					Overload(
						Const,
						Returns<DistanceType>(),
						Argument<const Vector&>("other")
					).Bind<Vector, &Vector::Dot>()
				),

				Function(
					"Unit",
					Overload(
						Const,
						Returns<Vector>()
					).Bind<Vector, &Vector::Unit>()
				),

				Function(
					"Length",
					Overload(
						Const,
						Returns<DistanceType>()
					).Bind<Vector, &Vector::Length>()
				),

				Function(
					"SquareLength",
					Overload(
						Const,
						Returns<DistanceType>()
					).Bind<Vector, &Vector::SquareLength>()
				),

				Function(
					"InvertedLength",
					Overload(
						Const,
						Returns<Vector>()
					).Bind<Vector, &Vector::InvertedLength>()
				),

				Function(
					"operator-",
					Overload(
						Const,
						Returns<Vector>()
					).Bind<Vector, &Vector::operator- >(),
					Overload(
						Const,
						Returns<Vector>(),
						Argument<const Vector&>("other")
					).Bind<Vector, &Vector::operator- >()
				),

				Function(
					"operator+",
					Overload(
						Const,
						Returns<Vector>(),
						Argument<const Vector&>("other")
					).Bind<Vector, &Vector::operator+>()
				),

				Function(
					"operator*",
					Overload(
						Const,
						Returns<Vector>(),
						Argument<Number>("scalar")
					).Bind<Vector, &Vector::operator*>(),
					Overload(
						Const,
						Returns<DistanceType>(),
						Argument<const Vector&>("other")
					).Bind<Vector, &Vector::operator*>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Vector&>("other")
					).Bind < Vector, &Vector::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Vector&>("other")
					).Bind < Vector, &Vector::operator!=>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Vector, &Vector::operator std::string>()
				)
			);
		}

		template <typename T>
		struct Vector2TypeAlias
		{
			static inline bool ShouldAlias = false;
		};

		template <>
		struct Vector2TypeAlias<Float>
		{
			static inline bool ShouldAlias = true;
		};

		template <>
		void ReflectType<Vector2>()
		{
			ReflectVector2<Vector2F, float, float>("Vector2F", Vector2TypeAlias<float>::ShouldAlias ? "Vector2" : nullptr);
			ReflectVector2<Vector2D, double, double>("Vector2D", Vector2TypeAlias<double>::ShouldAlias ? "Vector2" : nullptr);
			ReflectVector2<Vector2I, int, float>("Vector2I", nullptr);
		}
	}
}