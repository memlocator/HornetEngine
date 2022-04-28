#include "Minkowski2D.h"

#include <sstream>
#include <Windows.h>

namespace Engine
{
	namespace Physics
	{
		Vector3 GetCircleMinimumTranslationVector(const Vector3& difference, Float radius)
		{
			if (difference.SquareLength() == 0)
				return Vector3(0, radius);

			return (1 - radius / difference.Length()) * difference;
		}

		bool ObjectsAreColliding(const ColliderData& collider1, const ColliderData& collider2)
		{
			VertexVector difference;

			return false;
		}

		int FindLargestDotProduct(const Vector3& vector, const ColliderData& collider)
		{
			Float largestDot = vector * (collider.Center - collider.Vertices[0]);
			int largestDotIndex = 0;

			for (unsigned int i = 0; i < collider.Vertices.size(); ++i)
			{
				Float dot = vector * (collider.Center - collider.Vertices[i]);

				if (dot > largestDot)
				{
					largestDot = dot;
					largestDotIndex = i;
				}
			}

			return largestDotIndex;
		}

		VertexVector MinkowskiDifferenceBad(const ColliderData& collider1, const ColliderData& collider2)
		{
			VertexVector result;

			int size1 = int(collider1.Vertices.size());
			int size2 = int(collider2.Vertices.size());

			for (VertexVector::const_iterator i = collider2.Vertices.begin(); i != collider2.Vertices.end(); ++i)
				for (VertexVector::const_iterator j = collider1.Vertices.begin(); j != collider1.Vertices.end(); ++j)
					result.push_back(*i - *j);

			return result;
		}

		int FindFarthestVertex(const Vector3& vector, const ColliderData& collider)
		{
			int farthestIndex = 0;
			Float largestDot = collider.Vertices[0] * vector;

			for (unsigned int i = 1; i < collider.Vertices.size(); ++i)
			{
				Float dot = collider.Vertices[i] * vector;

				if (dot > largestDot)
				{
					largestDot = dot;
					farthestIndex = i;
				}
			}

			return farthestIndex;
		}

		Vector3 RightNormal(const Vector3& vector)
		{
			return Vector3(-vector.Y, vector.X);
		}

		Vector3 LeftNormal(const Vector3& vector)
		{
			return Vector3(vector.Y, -vector.X);
		}

		bool MeshContainsPoint(const VertexVector& mesh, const Vector3& point)
		{
			int size = int(mesh.size());

			for (int i = 0; i < size; ++i)
				if ((point - mesh[i]) * RightNormal(mesh[(i + 1) % size] - mesh[i]) > 0)
					return false;

			return true;
		}

		void MinkowskiDifference::Calculate(const ColliderData& collider1, const ColliderData& collider2)
		{
			int size1 = int(collider1.Vertices.size());
			int size2 = int(collider2.Vertices.size());
			int resultSize = size1 + size2;

			Vertices.resize(0);
			Normals.resize(0);
			Vertices.reserve(resultSize);
			Normals.reserve(resultSize);

			int i = collider1.TopVertex;
			int j = collider2.BottomVertex;

			Center = collider1.Center - collider2.Center;

			Vector3 lastPoint = collider1.Vertices[i] - collider2.Vertices[j];
			Vector3 lastNormal = lastPoint - Center;

			while ((int)Normals.size() < resultSize)
			{
				lastPoint = collider1.Vertices[i] - collider2.Vertices[j];
				Vertices.push_back(lastPoint);

				Vector3 nextNormal1 = collider1.Normals[i];
				Vector3 nextNormal2 = -collider2.Normals[j];

				if ((lastNormal * nextNormal1) > (lastNormal * nextNormal2))
				{
					lastNormal = nextNormal1;
					i = (i + 1) % size1;
				}
				else
				{
					lastNormal = nextNormal2;
					j = (j + 1) % size2;
				}

				Normals.push_back(lastNormal);
			}
		}

		bool MinkowskiDifference::Colliding()
		{
			int size = int(Vertices.size());

			for (int i = 0; i < size; ++i)
				if (Vertices[i] * Normals[i] < 0)
					return false;

			return true;
		}

		Vector3 MinkowskiDifference::MinimumTranslationVector()
		{
			int size = int(Vertices.size());

			Float closestDistance = Normals[0] * Vertices[0];
			Vector3 closestVector = closestDistance * Normals[0];

			for (int i = 1; i < size; ++i)
			{
				Float distance = Normals[i] * Vertices[i];

				if (distance < closestDistance)
				{
					closestDistance = distance;
					closestVector = distance * Normals[i];
				}
			}

			return closestVector;
		}

		void CircleMinkowskiDifference::Calculate(const ColliderData& collider, const Vector3& circleCenter, Float radius)
		{
			CircleRadius = radius;

			int size = int(collider.Vertices.size());

			Vertices.resize(0);
			Normals.resize(0);
			Vertices.reserve(2 * size);
			Normals.reserve(2 * size);

			Center = collider.Center - circleCenter;

			for (int i = 0; i < size; ++i)
			{
				Vertices.push_back(collider.Vertices[i] + radius * collider.Normals[i] - circleCenter);
				Normals.push_back(collider.Normals[i]);

				Vertices.push_back(collider.Vertices[(i + 1) % size] + radius * collider.Normals[i] - circleCenter);
				Normals.push_back(0.5f * (collider.Normals[i] + collider.Normals[(i + 1) % size]));
			}
		}

		bool CircleMinkowskiDifference::Colliding(int& circle)
		{
			circle = -1;

			bool colliding = MinkowskiDifference::Colliding();

			if (!colliding)
			{
				for (int i = 1; i < int(Vertices.size()); i += 2)
				{
					if (Vertices[i] * Normals[i] < 0 && (Vertices[i] - CircleRadius * Normals[i - 1]).SquareLength() <= CircleRadius * CircleRadius)
					{
						circle = i;
						return true;
					}
				}
			}

			return colliding;
		}

		Vector3 CircleMinkowskiDifference::MinimumTranslationVector(int circle)
		{
			int size = int(Vertices.size());

			if (circle != -1)
				return GetCircleMinimumTranslationVector(Vertices[circle] - CircleRadius * Normals[circle - 1], CircleRadius);
			else
			{
				Float closestDistance = Normals[0] * Vertices[0];
				Vector3 closestVector = closestDistance * Normals[0];

				for (int i = 2; i < size; i += 2)
				{
					Float distance = Normals[i] * Vertices[i];

					if (distance < closestDistance)
					{
						closestDistance = distance;
						closestVector = distance * Normals[i];
					}
				}

				return closestVector;
			}
		}

		Vector3 MinimumTranslationVector(const ColliderData& mesh, const Vector3& point)
		{
			int size = int(mesh.Vertices.size());

			Float closestDistance = mesh.Normals[0] * (mesh.Vertices[0] - point);
			Vector3 closestVector = closestDistance * mesh.Normals[0];

			for (int i = 1; i < size; ++i)
			{
				Float distance = mesh.Normals[i] * (mesh.Vertices[i] - point);

				if (distance < closestDistance)
				{
					closestDistance = distance;
					closestVector = distance * mesh.Normals[i];
				}
			}

			return closestVector;
		}

		Float LineIntersection(const Vector3& point1, const Vector3& vector, const Vector3& point2, const Vector3& normal)
		{
			return (normal * (point2 - point1)) / (normal * vector);
		}

		bool HittingSide(const Vector3& point1, const Vector3& vector, const Vector3& point2, const Vector3& normal)
		{
			Float numerator = normal * (point2 - point1);
			Float denominator = normal * vector;

			if (numerator < 0 && denominator < 0)
			{
				numerator = -numerator;
				denominator = -denominator;
			}

			return numerator >= -0.01f && numerator <= denominator;
		}

		bool VectorApproachesCollider(const Vector3& point, const Vector3& vector, const Vector3& center, Float radius)
		{
			Vector3 vector2 = center - point;
			Float projection = (vector * vector2) / (vector * vector);

			if (projection >= 0 && projection <= 1)
				return (vector2 - projection * vector).SquareLength() < radius;
			else
				return (vector2.SquareLength() < radius) || ((center - (point + vector)).SquareLength() < radius);
		}

		int GetEntrySide(const ColliderData& mesh, const Vector3& point, const Vector3& vector, Float& distance)
		{
			int size = int(mesh.Vertices.size());

			for (int i = 0; i < size; ++i)
			{
				if (mesh.Normals[i] * vector < 0 && HittingSide(mesh.Vertices[i], mesh.Vertices[(i + 1) % size] - mesh.Vertices[i], point, LeftNormal(vector)))
				{
					Float currentDistance = LineIntersection(point, vector, mesh.Vertices[i], mesh.Normals[i]);

					if (currentDistance > -0.01f && currentDistance < 1.01f)
					{
						distance = currentDistance;

						return i;
					}
				}
			}

			return -1;
		}

		int GetEntrySideFromStart(const ColliderData& mesh, const Vector3& point, const Vector3& vector, Float& distance, int startIndex)
		{
			int size = int(mesh.Vertices.size());

			int i = startIndex;

			while (mesh.Normals[i] * vector < 0)
			{
				if (HittingSide(mesh.Vertices[i], mesh.Vertices[(i + 1) % size] - mesh.Vertices[i], point, LeftNormal(vector)))
				{
					Float currentDistance = LineIntersection(point, vector, mesh.Vertices[i], mesh.Normals[i]);

					if (currentDistance > -0.01f && currentDistance < 1)
					{
						distance = currentDistance;

						return i;
					}
				}

				i = (i + 1) % size;
			}

			return -1;
		}

		void CalculateOffsetOnSide(const Vector3& vertex, Vector3& entryPoint, Vector3& velocity, Vector3& offset)
		{

			Vector3 vector = vertex - entryPoint;
			Float squareLength = vector.SquareLength();

			if (squareLength != 0)
			{
				Float dot = (vector * velocity) / squareLength;
				Float distance = 1 / dot;

				if (dot > 1)
					dot = 1;

				if (distance > 1)
					distance = 1;

				offset += dot * vector - distance * velocity;
				velocity = (1 - distance) * velocity;
				entryPoint += dot * vector;
			}
		}

		Vector3 GetVelocityOffsetClockwise(const ColliderData& mesh, Vector3 velocity, int entrySide, Vector3 entryPoint)
		{
			int size = int(mesh.Vertices.size());
			int i = entrySide;
			Vector3 offset;

			while (mesh.Normals[i] * velocity < 0 && velocity.SquareLength() > 0)
			{
				i = (i + 1) % size;

				CalculateOffsetOnSide(mesh.Vertices[i], entryPoint, velocity, offset);
			}

			return offset;
		}

		Vector3 GetVelocityOffsetCounterClockwise(const ColliderData& mesh, Vector3 velocity, int entrySide, Vector3 entryPoint)
		{
			int size = int(mesh.Vertices.size());
			int i = entrySide;
			Vector3 offset;

			while (mesh.Normals[i] * velocity < 0 && velocity.SquareLength() > 0)
			{
				CalculateOffsetOnSide(mesh.Vertices[i], entryPoint, velocity, offset);

				i = (i == 0 ? size : i) - 1;
			}

			return offset;
		}

		Vector3 GetVelocityOffset(const ColliderData& mesh, Vector3 velocity, int entrySide, Vector3 entryPoint, bool clockwise)
		{
			int size = int(mesh.Vertices.size());
			int i = entrySide;
			Vector3 offset;

			while (mesh.Normals[i] * velocity < 0 && velocity.SquareLength() > 0)
			{
				if (clockwise)
				{
					i = (i + 1) % size;

					CalculateOffsetOnSide(mesh.Vertices[i], entryPoint, velocity, offset);
				}
				else
				{
					CalculateOffsetOnSide(mesh.Vertices[i], entryPoint, velocity, offset);

					i = (i == 0 ? size : i) - 1;
				}
			}

			return offset;
		}

		Vector3 GetVelocityOffset(const ColliderData& mesh, Vector3 velocity)
		{
			Float distance;
			int entrySide = GetEntrySide(mesh, Vector3(), velocity, distance);

			if (entrySide != -1)
			{
				Vector3 entryPoint = distance * velocity;

				return GetVelocityOffset(mesh, velocity - entryPoint, entrySide, entryPoint, LeftNormal(mesh.Normals[entrySide]) * velocity > 0);
			}
			else
				return Vector3();
		}

		void GetClosestCollision(const ColliderInfoVector& colliders, Vector3 point, Vector3 velocity, ColliderInfoVector::const_iterator& ignore, ColliderInfoVector::const_iterator& closestCollider, Float& closestDistance, int& closestSide)
		{
			closestCollider = colliders.begin();
			closestSide = -1;

			for (ColliderInfoVector::const_iterator i = colliders.begin(); i != colliders.end(); ++i)
			{
				if (i != ignore && VectorApproachesCollider(point, velocity, i->Collider->Center, i->Collider->RadiusSquared))
				{
					Float distance;
					int side = GetEntrySide(*i->Collider, point, velocity, distance);

					if (distance >= -1e-3 && side != -1 && (closestSide == -1 || distance <= closestDistance) && (i->LastHitIndex == -1 || (LeftNormal(i->Collider->Normals[side]) * velocity > 0) == i->Clockwise))
					{
						closestCollider = i;
						closestDistance = distance;
						closestSide = side;
					}
				}
			}
		}

		Vector3 GetVelocityOffset(ColliderInfoVector& differences, ColliderInfoVector::iterator& mesh, Vector3& velocity, int entrySide, Vector3& entryPoint, bool clockwise, ColliderInfoVector::iterator& hitObject, int& hitSide)
		{
			int size = int(mesh->Collider->Vertices.size());
			int i = entrySide;
			Vector3 offset;
			Vector3 lastEntryPoint = entryPoint;
			Vector3 lastVelocity = velocity;

			while (mesh->Collider->Normals[i] * velocity < 0 && velocity.SquareLength() > 0)
			{
				Vector3 lastOffset = offset;

				if (clockwise)
				{
					i = (i + 1) % size;

					CalculateOffsetOnSide(mesh->Collider->Vertices[i], entryPoint, velocity, offset);
				}
				else
				{
					CalculateOffsetOnSide(mesh->Collider->Vertices[i], entryPoint, velocity, offset);

					i = (i == 0 ? size : i) - 1;
				}

				Vector3 vector = entryPoint - lastEntryPoint;

				Float distance;
				GetClosestCollision(differences, lastEntryPoint, vector, mesh, hitObject, distance, hitSide);

				if (hitSide != -1)
				{
					entryPoint = lastEntryPoint + distance * vector;
					Vector3 vel = velocity;
					Vector3 velocityDelta = lastVelocity - velocity;
					Vector3 restoredVelocity = (1 - distance) * velocityDelta;
					velocity += restoredVelocity;
					offset += restoredVelocity - (1 - distance) * vector;

					Float d = LeftNormal(hitObject->Collider->Normals[hitSide]) * vector;
					if (clockwise == (LeftNormal(hitObject->Collider->Normals[hitSide]) * velocity < 0))
					{
						offset -= velocity + vel;
						velocity.Set(0, 0);
					}

					return offset;
				}

				lastEntryPoint = entryPoint;
				lastVelocity = velocity;
			}

			return offset;
		}

		Vector3 GetVelocityOffset(ColliderInfoVector& differences, Vector3 velocity)
		{
			Vector3 offset;
			Vector3 entryPoint;

			ColliderInfoVector::iterator lastCollision = differences.end();

			while (velocity.SquareLength() > 0)
			{
				ColliderInfoVector::iterator collider;
				Float distance;
				int side;

				GetClosestCollision(differences, entryPoint, velocity, lastCollision, collider, distance, side);

				if (side == -1)
					break;
				else
				{
					entryPoint += distance * velocity;
					bool clockwise = LeftNormal(collider->Collider->Normals[side]) * velocity > 0;
					int hitSide;
					ColliderInfoVector::iterator hitObject;
					velocity *= 1 - distance;
					offset += GetVelocityOffset(differences, collider, velocity, side, entryPoint, clockwise, hitObject, hitSide);
					lastCollision = collider;
				}
			}

			return offset;
		}

		bool VectorCanHitSide(const Vector3& normal, const Vector3& vector)
		{
			return normal * vector < 0;
		}

		bool TravelClockwise(const Vector3& normal, const Vector3& velocity)
		{
			return LeftNormal(normal) * velocity > 0;
		}

		void GetCollisionCandidates(const ColliderVector& differences, const Vector3& velocity, LineVector& results)
		{
			for (ColliderVector::const_iterator i = differences.begin(); i != differences.end(); ++i)
			{
				int size = int(i->Vertices.size());

				for (int j = 0; j < size; ++j)
					if (i->Normals[j] * velocity < 0)
						results.push_back({ i->Vertices[j], i->Vertices[(j + 1) % size], i->Normals[j] });
			}
		}
	}
}