#include "Vector3.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <typename Vector, typename Number, typename DistanceType, typename... Allowed>
		void ReflectVector3(const char* name, const char* alias)
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
				Member<Bind(&Vector::W)>("W"),

				Constructor(
					Overload()
				),

				Constructor(
					Overload(
						Argument<Number, Default((Number)0.0)>("x"),
						Argument<Number, Default((Number)0.0)>("y"),
						Argument<Number, Default((Number)0.0)>("z"),
						Argument<Number, Default((Number)0.0)>("w")
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
					).Bind<Vector, &Vector::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Vector&>("other")
					).Bind<Vector, &Vector::operator!=>()
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
		struct Vector3TypeAlias
		{
			static inline bool ShouldAlias = false;
		};

		template <>
		struct Vector3TypeAlias<Float>
		{
			static inline bool ShouldAlias = true;
		};

		template <>
		void ReflectType<Vector3>()
		{
			ReflectVector3<Vector3F, float, float>("Vector3F", Vector3TypeAlias<float>::ShouldAlias ? "Vector3" : nullptr);
			ReflectVector3<Vector3D, double, double>("Vector3D", Vector3TypeAlias<double>::ShouldAlias ? "Vector3" : nullptr);
			ReflectVector3<Vector3I, int, float>("Vector3I", nullptr);
		}
	}
}