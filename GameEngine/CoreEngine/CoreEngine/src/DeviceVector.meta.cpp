#include "DeviceVector.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<DeviceAxis>()
		{
			Reflect<DeviceAxis>::Type(
				"DeviceAxis",

				Member<Bind(&DeviceAxis::Scale)>("Scale"),
				Member<Bind(&DeviceAxis::Offset)>("Offset"),

				Constructor(
					Overload(
						Argument<Float, Default(0.0f)>("scale"),
						Argument<Float, Default(0.0f)>("offset")
					)
				),

				Function(
					"Set",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<Float>("newScale"),
						Argument<Float>("newOffset")
					).Bind<DeviceAxis, &DeviceAxis::Set>()
				),

				Function(
					"Calculate",
					Overload(
						Const,
						Returns<Float>(),
						Argument<Float>("base"),
						Argument<Float>("size")
					).Bind<DeviceAxis, &DeviceAxis::Calculate>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const DeviceAxis&>("other")
					).Bind < DeviceAxis, &DeviceAxis::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const DeviceAxis&>("other")
					).Bind < DeviceAxis, &DeviceAxis::operator!=>()
				),

				Function(
					"operator+",
					Overload(
						Const,
						Returns<DeviceAxis>(),
						Argument<const DeviceAxis&>("other")
					).Bind<DeviceAxis, &DeviceAxis::operator+>()
				),

				Function(
					"operator-",
					Overload(
						Const,
						Returns<DeviceAxis>(),
						Argument<const DeviceAxis&>("other")
					).Bind<DeviceAxis, &DeviceAxis::operator- >(),
					Overload(
						Const,
						Returns<DeviceAxis>()
					).Bind<DeviceAxis, &DeviceAxis::operator- >()
				),

				Function(
					"operator*",
					Overload(
						Const,
						Returns<DeviceAxis>(),
						Argument<Float>("scalar")
					).Bind<DeviceAxis, &DeviceAxis::operator*>()
				),

				Function(
					"operator/",
					Overload(
						Const,
						Returns<DeviceAxis>(),
						Argument<Float>("scalar")
					).Bind<DeviceAxis, &DeviceAxis::operator/>()
				)
			);
		}

		template <>
		void ReflectType<DeviceVector>()
		{
			Reflect<DeviceVector>::Type(
				"DeviceVector",

				Member<Bind(&DeviceVector::X)>("X"),
				Member<Bind(&DeviceVector::Y)>("Y"),

				Constructor(
					Overload(
						Argument<Float, Default(0.0f)>("xScale"),
						Argument<Float, Default(0.0f)>("xOffset"),
						Argument<Float, Default(0.0f)>("yScale"),
						Argument<Float, Default(0.0f)>("yOffset")
					)
				),

				Function(
					"Set",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<Float>("xScale"),
						Argument<Float>("xOffset"),
						Argument<Float>("yScale"),
						Argument<Float>("yOffset")
					).Bind<DeviceVector, &DeviceVector::Set>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const DeviceAxis&>("x"),
						Argument<const DeviceAxis&>("y")
					).Bind<DeviceVector, &DeviceVector::Set>()
				),

				Function(
					"Calculate",
					Overload(
						Const,
						Returns<Vector3>(),
						Argument<const Vector3&>("base"),
						Argument<const Vector3&>("size")
					).Bind<DeviceVector, &DeviceVector::Calculate>(),
					Overload(
						Const,
						Returns<Vector3>(),
						Argument<Float>("baseX"),
						Argument<Float>("sizeX"),
						Argument<Float>("baseY"),
						Argument<Float>("sizeY")
					).Bind<DeviceVector, &DeviceVector::Calculate>()
				),

				Function(
					"operator==",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const DeviceVector&>("other")
					).Bind<DeviceVector, &DeviceVector::operator==>()
				),

				Function(
					"operator!=",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const DeviceVector&>("other")
					).Bind<DeviceVector, &DeviceVector::operator!=>()
				),

				Function(
					"operator+",
					Overload(
						Const,
						Returns<DeviceVector>(),
						Argument<const DeviceVector&>("other")
					).Bind<DeviceVector, &DeviceVector::operator+>()
				),

				Function(
					"operator-",
					Overload(
						Const,
						Returns<DeviceVector>(),
						Argument<const DeviceVector&>("other")
					).Bind<DeviceVector, &DeviceVector::operator- >(),
					Overload(
						Const,
						Returns<DeviceVector>()
					).Bind<DeviceVector, &DeviceVector::operator- >()
				),

				Function(
					"operator*",
					Overload(
						Const,
						Returns<DeviceVector>(),
						Argument<Float>("scalar")
					).Bind<DeviceVector, &DeviceVector::operator*>()
				),

				Function(
					"operator/",
					Overload(
						Const,
						Returns<DeviceVector>(),
						Argument<Float>("scalar")
					).Bind<DeviceVector, &DeviceVector::operator/>()
				)
			);
		}
	}
}