#include "Vector3S.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <typename Vector, typename Number, typename DistanceType, typename... Allowed>
		void ReflectVector3S(const char* name, const char* alias)
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
					Overload()
				),

				Constructor(
					Overload(
						Argument<Number, Default((Number)0.0)>("x"),
						Argument<Number, Default((Number)0.0)>("y"),
						Argument<Number, Default((Number)0.0)>("z")
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
					"Cross",
					Overload(
						Const,
						Returns<Vector>(),
						Argument<const Vector&>("other")
					).Bind<Vector, &Vector::Cross>()
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
		struct Vector3STypeAlias
		{
			static inline bool ShouldAlias = false;
		};

		template <>
		struct Vector3STypeAlias<Float>
		{
			static inline bool ShouldAlias = true;
		};

		template <>
		void ReflectType<Vector3S>()
		{
			ReflectVector3S<Vector3SF, float, float>("Vector3SF", Vector3STypeAlias<float>::ShouldAlias ? "Vector3S" : nullptr);
			ReflectVector3S<Vector3SD, double, double>("Vector3SD", Vector3STypeAlias<double>::ShouldAlias ? "Vector3S" : nullptr);
			ReflectVector3S<Vector3SI, int, float>("Vector3SI", nullptr);
		}
	}
}