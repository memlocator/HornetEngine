#include "BoundingSphere.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<BoundingSphere>()
		{
			Reflect<BoundingSphere>::Type(
				"Aabb",

				Member<Bind(&BoundingSphere::Radius)>("Radius"),
				Member<Bind(&BoundingSphere::Center)>("Center"),

				Constructor(
					Overload(
						Argument<float, Default(0.0f)>("radius"),
						Argument<const Vector3&, Default(Vector3())>("center")
					)
				),

				Function(
					"Contains",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const Vector3&>("point")
					).Bind<BoundingSphere, &BoundingSphere::Contains>()
				),

				Function(
					"ExpandByPoint",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("point")
					).Bind<BoundingSphere, &BoundingSphere::ExpandByPoint>()
				)
			);
		}
	}
}