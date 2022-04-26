#include "Collider2D.h"

#include "ColliderAsset.h"
#include "CollisionGroup.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace Engine::Physics;

		template <>
		void ReflectType<Collision>()
		{
			Reflect<Collision>::Type
			(
				"Collision",

				Constructor(
					Overload()
				),

				Member<Bind(&Collision::OtherCollider)>("OtherCollider"),
				Member<Bind(&Collision::ContactPoint)>("ContactPoint"),
				Member<Bind(&Collision::Displacement)>("Displacement")
			);
		}

		template <>
		void ReflectType<Collider2D>()
		{
			Reflect<Collider2D, Object>::Class
			(
				"Collider2D",
				{ "GameObject", "Physics" },

				Constructor(
					Overload()
				),

				Member<Bind(&Collider2D::IsCircle)>("IsCircle"),
				Member<Bind(&Collider2D::Group)>("Group"),
				Member<Bind(&Collider2D::Asset)>("Asset"),
				//Member<Bind(&Collider2D::Data)>("Data"),

				Function(
					"UpdateData",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<Collider2D, &Collider2D::UpdateData>()
				),

				Function(
					"GetBoundingBox",
					Overload(
						Const,
						Returns<Aabb>()
					).Bind<Collider2D, &Collider2D::GetBoundingBox>()
				),

				Function(
					"HasMoved",
					Overload(
						Const,
						Returns<bool>()
					).Bind<Collider2D, &Collider2D::HasMoved>()
				),

				Function(
					"GetRadius",
					Overload(
						Const,
						Returns<float>()
					).Bind<Collider2D, &Collider2D::GetRadius>()
				),

				Function(
					"GetCenter",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Collider2D, &Collider2D::GetCenter>()
				),

				Function(
					"GetWidth",
					Overload(
						Const,
						Returns<float>(),
						Argument<const Vector3&>("axis")
					).Bind<Collider2D, &Collider2D::GetWidth>()
				),

				Function(
					"CanCollideWith",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const std::shared_ptr<Collider2D>&>("otherCollider")
					).Bind<Collider2D, &Collider2D::CanCollideWith>()
				),

				Function(
					"Collided",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const CollisionPair&>("collision")
					).Bind<Collider2D, &Collider2D::Collided>()
				),

				Function(
					"GetCollisions",
					Overload(
						Const,
						Returns<int>()
					).Bind<Collider2D, &Collider2D::GetCollisions>()
				),
				
				Function(
					"GetCollision",
					Overload(
						Const,
						Returns<Collision>(),
						Argument<int>("index")
					).Bind<Collider2D, &Collider2D::GetCollision>()
				)
			);
		}

		template <>
		void ReflectType<CollisionPair>()
		{
			Reflect<CollisionPair>::Type
			(
				"CollisionPair",

				Constructor(
					Overload()
				),

				Member<Bind(&CollisionPair::Collider1)>("Collider1"),
				Member<Bind(&CollisionPair::Collider2)>("Collider2"),
				Member<Bind(&CollisionPair::ContactPoint)>("ContactPoint"),
				Member<Bind(&CollisionPair::Displacement)>("Displacement")
			);
		}
	}
}