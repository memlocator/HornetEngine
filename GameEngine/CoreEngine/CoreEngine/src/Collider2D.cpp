#include "Collider2D.h"

import <algorithm>;

#include "Transform.h"
#include "RigidBody.h"
#include "ColliderAsset.h"
#include "CollisionGroup.h"

namespace Engine
{
	namespace Physics
	{
		void Collider2D::Initialize()
		{
			Object::Initialize();
		}

		void Collider2D::UpdateData()
		{
			Collisions.clear();

			std::shared_ptr<Transform> transform = GetComponent<Transform>();

			Matrix4 transformation;

			if (transform != nullptr)
				transformation = transform->GetWorldTransformation();

			Aabb boundingBox;

			if (IsCircle)
			{
				Vector3 scale = transformation.ExtractScale();

				Center = transformation.Translation();
				Radius = std::max(std::max(scale.X, scale.Y), scale.Z);

				boundingBox = Aabb(
					Center - Vector3(Radius, Radius, 1._F),
					Center + Vector3(Radius, Radius, 1._F)
				);
			}
			else
			{
				if (!Asset.expired())
					Data.TransformFrom(Asset.lock()->Data, transformation);
				else
					Data = ColliderData();

				boundingBox = Data.BoundingBox;
			}

			Moved = BoundingBox != boundingBox;

			BoundingBox = boundingBox;
		}

		Aabb Collider2D::GetBoundingBox() const
		{
			return BoundingBox;
		}

		bool Collider2D::HasMoved() const
		{
			return Moved;
		}

		Float Collider2D::GetRadius() const
		{
			return Radius;
		}

		Vector3 Collider2D::GetCenter() const
		{
			return Center;
		}

		Float Collider2D::GetWidth(const Vector3& axis) const
		{
			if (IsCircle)
				return 2 * Radius;

			if (Data.Vertices.size() == 0)
				return 0;

			Float min = std::numeric_limits<Float>::max();
			Float max = std::numeric_limits<Float>::lowest();

			Vector3 vector = axis;
			vector.Normalize();

			for (int i = 0; i < int(Data.Vertices.size()); ++i)
			{
				Float dot = Data.Vertices[i] * vector;

				min = std::min(min, dot);
				max = std::max(max, dot);
			}

			return max - min;
		}

		bool Collider2D::CanCollideWith(const std::shared_ptr<Collider2D>& other) const
		{
			if ((!IsCircle && Asset.lock()) || Group.lock())
				return false;

			if ((!other->IsCircle && other->Asset.expired()) || other->Group.expired())
				return false;

			if (Group.lock()->GetInteraction(other->Group.lock()) == Enum::InteractionType::None)
				return false;

			return true;
		}

		void Collider2D::Collided(const CollisionPair& collisionPair)
		{
			Collision collision;

			collision.ContactPoint = collisionPair.ContactPoint;
			collision.Displacement = collisionPair.Displacement;

			if (collisionPair.Collider1 == This.lock())
				collision.OtherCollider = collisionPair.Collider2;
			else
			{
				collision.OtherCollider = collisionPair.Collider1;
				collision.Displacement *= -1;
			}

			std::shared_ptr<RigidBody> body = GetComponent<RigidBody>();
			std::shared_ptr<RigidBody> otherBody = collision.OtherCollider.lock()->GetComponent<RigidBody>();

			Float mass1 = body->GetMass();
			Float mass2 = otherBody->GetMass();
			Float massSum = mass1 + mass2;

			if (massSum == 0)
				massSum = 1;

			Float coefficient = (massSum - mass1) / massSum;

			if (mass1 == 0)
				coefficient = 0;
			else if (mass2 == 0)
				coefficient = 1;

			if (Group.lock()->GetInteraction(collision.OtherCollider.lock()->Cast<Collider2D>()->Group.lock()) == Enum::InteractionType::Resolve)
				body->ProcessDisplacement(coefficient * collision.Displacement, collision.ContactPoint);

			Collisions.push_back(collision);
		}

		int Collider2D::GetCollisions() const
		{
			return int(Collisions.size());
		}

		Collision Collider2D::GetCollision(int index) const
		{
			return Collisions[index];
		}
	}
}