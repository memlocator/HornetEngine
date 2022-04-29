#include "DeviceTransform.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<DeviceTransform>()
		{
			Reflect<DeviceTransform, Object>::Class
			(
				"DeviceTransform",
				{ "GameObject" },

				Member<Bind(&DeviceTransform::Enabled)>("Enabled"),
				Member<Bind(&DeviceTransform::Visible)>("Visible"),
				Member<Bind(&DeviceTransform::InheritTransformation)>("InheritTransformation"),
				Member<Bind(&DeviceTransform::AspectRatio)>("AspectRatio"),
				Member<Bind(&DeviceTransform::Rotation)>("Rotation"),
				Member<Bind(&DeviceTransform::Size)>("Size"),
				Member<Bind(&DeviceTransform::Position)>("Position"),
				Member<Bind(&DeviceTransform::AnchorPoint)>("AnchorPoint"),
				Member<Bind(&DeviceTransform::RotationAnchor)>("RotationAnchor"),

				Constructor(
					Overload()
				),

				Function(
					"GetTransformation",
					Overload(
						Mutable,
						Returns<Matrix4>()
					).Bind<DeviceTransform, &DeviceTransform::GetTransformation>()
				),

				Function(
					"GetInverseTransformation",
					Overload(
						Mutable,
						Returns<Matrix4>()
					).Bind<DeviceTransform, &DeviceTransform::GetInverseTransformation>()
				),

				Function(
					"GetAbsoluteSize",
					Overload(
						Mutable,
						Returns<Vector3>()
					).Bind<DeviceTransform, &DeviceTransform::GetAbsoluteSize>()
				),

				Function(
					"GetAbsolutePosition",
					Overload(
						Mutable,
						Returns<Vector3>(),
						Argument<const DeviceVector&, Default(DeviceVector())>("point")
					).Bind<DeviceTransform, &DeviceTransform::GetAbsolutePosition>()
				),

				Function(
					"GetLocalPosition",
					Overload(
						Mutable,
						Returns<Vector3>(),
						Argument<const DeviceVector&, Default(DeviceVector())>("point")
					).Bind<DeviceTransform, &DeviceTransform::GetLocalPosition>()
				),

				Function(
					"GetResolution",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<DeviceTransform, &DeviceTransform::GetResolution>()
				),

				Function(
					"ContainsLocalPoint",
					Overload(
						Mutable,
						Returns<bool>(),
						Argument<const Vector3&>("point")
					).Bind<DeviceTransform, &DeviceTransform::ContainsLocalPoint>()
				),

				Function(
					"ContainsPoint",
					Overload(
						Mutable,
						Returns<bool>(),
						Argument<const Vector3&>("point")
					).Bind<DeviceTransform, &DeviceTransform::ContainsPoint>()
				),

				Function(
					"HasMoved",
					Overload(
						Const,
						Returns<bool>()
					).Bind<DeviceTransform, &DeviceTransform::HasMoved>()
				),

				Function(
					"IsVisible",
					Overload(
						Const,
						Returns<bool>()
					).Bind<DeviceTransform, &DeviceTransform::IsVisible>()
				),

				Function(
					"IsEnabled",
					Overload(
						Const,
						Returns<bool>()
					).Bind<DeviceTransform, &DeviceTransform::IsEnabled>()
				),

				Function(
					"UpdateTransformation",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<DeviceTransform, &DeviceTransform::UpdateTransformation>()
				)
			);
		}
	}
}