#include "Aabb.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Aabb>()
		{
			Reflect<Aabb>::Type(
				"Aabb",

				Member<Bind(&Aabb::Min)>("Min"),
				Member<Bind(&Aabb::Max)>("Max"),

				Constructor(
					Overload(
						Argument<const Vector3&, Default(Vector3())>("min"),
						Argument<const Vector3&, Default(Vector3())>("max")
					)
				),

				Function(
					"GetCenter",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Aabb, &Aabb::GetCenter>()
				),

				Function(
					"GetSize",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Aabb, &Aabb::GetSize>()
				),

				Function(
					"ContainsPoint",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Vector3&>("point")
					).Bind<Aabb, &Aabb::ContainsPoint>()
				),

				Function(
					"Intersects",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Aabb&>("box")
					).Bind<Aabb, &Aabb::Intersects>()//,
					//Overload(
					//	Const,
					//	Returns<Enum::IntersectionType>(),
					//	Argument<const Plane&>("plane"),
					//	Argument<float, Default(1e-5f)>("epsilon")
					//).Bind<Aabb, &Aabb::Intersects>()
				),

				Function(
					"InRange",
					Overload(
						Const,
						Returns<bool>(),
						Argument<Float>("x"),
						Argument<Float>("min"),
						Argument<Float>("max")
					).Bind<Aabb, &Aabb::InRange>()
				),

				Function(
					"Transform",
					Overload(
						Const,
						Returns<Aabb>(),
						Argument<const Matrix4&>("transformation")
					).Bind<Aabb, &Aabb::Transform>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Aabb&>("other")
					).Bind<Aabb, &Aabb::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Aabb&>("other")
					).Bind<Aabb, &Aabb::operator!=>()
				)
			);
		}
	}
}
