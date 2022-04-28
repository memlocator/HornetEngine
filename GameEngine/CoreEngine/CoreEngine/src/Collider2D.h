#pragma once

#include "Object.h"

#include "Aabb.h"
#include "ColliderData.h"

namespace Engine
{
	namespace Physics
	{
		struct CollisionPair;
		class CollisionGroup;
		class ColliderAsset;
		class Collider2D;

		class Collision
		{
		public:
			std::weak_ptr<Collider2D> OtherCollider;
			Vector3 ContactPoint;
			Vector3 Displacement;
		};

		class Collider2D : public Object
		{
		public:
			bool IsCircle = false;
			std::weak_ptr<CollisionGroup> Group;
			std::weak_ptr<ColliderAsset> Asset;
			ColliderData Data;

			~Collider2D() {}

			void Initialize();
			void Update(Float) {}

			void UpdateData();
			Aabb GetBoundingBox() const;
			bool HasMoved() const;
			Float GetRadius() const;
			Vector3 GetCenter() const;
			Float GetWidth(const Vector3& axis) const;
			bool CanCollideWith(const std::shared_ptr<Collider2D>& otherCollider) const;
			void Collided(const CollisionPair& collisionPair);
			int GetCollisions() const;
			Collision GetCollision(int index) const;

		private:

			typedef std::vector<Collision> CollisionVector;

			bool Moved = false;
			Float Radius = 0;
			Aabb BoundingBox;
			Vector3 Center;
			CollisionVector Collisions;
		};
	}

	using Physics::Collision;

	namespace Physics
	{
		struct CollisionPair
		{
			std::shared_ptr<Collider2D> Collider1;
			std::shared_ptr<Collider2D> Collider2;

			Vector3 ContactPoint;
			Vector3 Displacement;
		};
	}
}