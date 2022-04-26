#include "RigidBody.h"

#include "PointMass.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace Engine::Physics;

		template <>
		void ReflectType<RigidBody>()
		{
			Reflect<RigidBody, Object>::Class
			(
				"RigidBody",
				{ "GameObject", "Physics"},

				Constructor(
					Overload()
				),

				Member<Bind(&RigidBody::Velocity)>("Velocity"),
				Member<Bind(&RigidBody::Torque)>("Torque"),

				Function(
					"AddForce",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("force"),
						Argument<const Vector3&, Default(Vector3())>("position")
					).Bind<RigidBody, &RigidBody::AddForce>()
				),

				Function(
					"GetForceCount",
					Overload(
						Const,
						Returns<int>()
					).Bind<RigidBody, &RigidBody::GetForceCount>()
				),

				Function(
					"GetForce",
					Overload(
						Const,
						Returns<Vector3>(),
						Argument<int>("index")
					).Bind<RigidBody, &RigidBody::GetForce>()
				),

				Function(
					"GetPointMassCount",
					Overload(
						Const,
						Returns<int>()
					).Bind<RigidBody, &RigidBody::GetPointMassCount>()
				),

				Function(
					"GetPointMass",
					Overload(
						Mutable,
						Returns<std::shared_ptr<PointMass>>(),
						Argument<int>("index")
					).Bind<RigidBody, &RigidBody::GetPointMass>()
				),

				Function(
					"GetMass",
					Overload(
						Const,
						Returns<float>()
					).Bind<RigidBody, &RigidBody::GetMass>()
				),

				Function(
					"GetCenterOfMass",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<RigidBody, &RigidBody::GetCenterOfMass>()
				),

				Function(
					"ProcessDisplacement",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("displacement"),
						Argument<const Vector3&, Default(Vector3())>("position")
					).Bind<RigidBody, &RigidBody::ProcessDisplacement>()
				),

				Function(
					"AddMass",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<PointMass>&>("mass")
					).Bind<RigidBody, &RigidBody::AddMass>()
				),

				Function(
					"RemoveMass",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<PointMass>&>("mass")
					).Bind<RigidBody, &RigidBody::RemoveMass>()
				),

				Function(
					"HasMass",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const std::shared_ptr<PointMass>&>("mass")
					).Bind<RigidBody, &RigidBody::HasMass>()
				)
			);
		}
	}
}