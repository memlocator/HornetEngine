#include "Transform.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Transform>()
		{
			Reflect<Transform, Object>::Class
			(
				"Transform",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Property(
					"IsStatic",
					Getter<bool>(Const).Bind<Transform, &Transform::IsTransformStatic>(),
					Setter<bool>(Mutable).Bind<Transform, &Transform::SetStatic>()
				),

				Property(
					"Transformation",
					Getter<const Matrix4&>(Mutable).Bind<Transform, &Transform::GetTransformation>(),
					Setter<const Matrix4&>(Mutable).Bind<Transform, &Transform::SetTransformation>()
				),

				Property(
					"InheritTransformation",
					Getter<bool>(Const).Bind<Transform, &Transform::InheritsTransformation>(),
					Setter<bool>(Mutable).Bind<Transform, &Transform::SetInheritsTransformation>()
				),

				Function(
					"HasMoved",
					Overload(
						Mutable,
						Returns<bool>()
					).Bind<Transform, &Transform::HasMoved>()
				),

				Function(
					"SetStatic",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<bool>("isStatic")
					).Bind<Transform, &Transform::SetStatic>()
				),

				Function(
					"IsTransformStatic",
					Overload(
						Const,
						Returns<bool>()
					).Bind<Transform, &Transform::IsTransformStatic>()
				),

				Function(
					"SetTransformation",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Matrix4&>("matrix")
					).Bind<Transform, &Transform::SetTransformation>()
				),

				Function(
					"GetTransformation",
					Overload(
						Mutable,
						Returns<const Matrix4&>()
					).Bind<Transform, &Transform::GetTransformation>()
				),

				Function(
					"SetInheritsTransformation",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<bool>("inherits")
					).Bind<Transform, &Transform::SetInheritsTransformation>()
				),

				Function(
					"InheritsTransformation",
					Overload(
						Const,
						Returns<bool>()
					).Bind<Transform, &Transform::InheritsTransformation>()
				),

				Function(
					"GetPosition",
					Overload(
						Mutable,
						Returns<Vector3>()
					).Bind<Transform, &Transform::GetPosition>()
				),

				Function(
					"SetPosition",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("position")
					).Bind<Transform, &Transform::SetPosition>()
				),

				Function(
					"Move",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("offset")
					).Bind<Transform, &Transform::Move>()
				),

				Function(
					"GetWorldPosition",
					Overload(
						Mutable,
						Returns<Vector3>()
					).Bind<Transform, &Transform::GetWorldPosition>()
				),

				Function(
					"GetWorldTransformation",
					Overload(
						Mutable,
						Returns<const Matrix4&>()
					).Bind<Transform, &Transform::GetWorldTransformation>()
				),

				Function(
					"GetWorldTransformationInverse",
					Overload(
						Mutable,
						Returns<const Matrix4&>()
					).Bind<Transform, &Transform::GetWorldTransformationInverse>()
				),

				Function(
					"GetWorldRotation",
					Overload(
						Mutable,
						Returns<const Matrix4&>()
					).Bind<Transform, &Transform::GetWorldRotation>()
				),

				Function(
					"GetWorldOrientation",
					Overload(
						Mutable,
						Returns<Quaternion>()
					).Bind<Transform, &Transform::GetWorldOrientation>()
				),

				Function(
					"GetWorldNormalTransformation",
					Overload(
						Mutable,
						Returns<const Matrix4&>()
					).Bind<Transform, &Transform::GetWorldNormalTransformation>()
				),

				Function(
					"GetOrientation",
					Overload(
						Mutable,
						Returns<Quaternion>()
					).Bind<Transform, &Transform::GetOrientation>()
				),

				Function(
					"SetOrientation",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Quaternion&>("orientation")
					).Bind<Transform, &Transform::SetOrientation>()
				),

				Function(
					"Rotate",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Quaternion&>("rotation")
					).Bind<Transform, &Transform::Rotate>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("axis"),
						Argument<float>("angle")
					).Bind<Transform, &Transform::Rotate>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("angles")
					).Bind<Transform, &Transform::Rotate>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<float>("pitch"),
						Argument<float>("yaw"),
						Argument<float>("roll")
					).Bind<Transform, &Transform::Rotate>()
				),

				Function(
					"GetEulerAnglesYaw",
					Overload(
						Mutable,
						Returns<Vector3>()
					).Bind<Transform, &Transform::GetEulerAnglesYaw>()
				),

				Function(
					"RotateYaw",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("angles")
					).Bind<Transform, &Transform::RotateYaw>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<float>("yaw"),
						Argument<float>("pitch"),
						Argument<float>("roll")
					).Bind<Transform, &Transform::RotateYaw>()
				),

				Function(
					"GetScale",
					Overload(
						Mutable,
						Returns<Vector3>()
					).Bind<Transform, &Transform::GetScale>()
				),

				Function(
					"SetScale",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("scale")
					).Bind<Transform, &Transform::SetScale>()
				),

				Function(
					"Rescale",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("scale")
					).Bind<Transform, &Transform::Rescale>()
				),

				Function(
					"TransformBy",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Matrix4&>("transformation")
					).Bind<Transform, &Transform::TransformBy>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Quaternion&>("transformation"),
						Argument<const Vector3&, Default(Vector3())>("point")
					).Bind<Transform, &Transform::TransformBy>()
				),

				Function(
					"TransformByRelative",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Matrix4&>("transformation")
					).Bind<Transform, &Transform::TransformByRelative>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Quaternion&>("transformation"),
						Argument<const Vector3&, Default(Vector3())>("point")
					).Bind<Transform, &Transform::TransformByRelative>()
				)
			);
		}
	}
}