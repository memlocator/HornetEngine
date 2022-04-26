#include "PointGenerator.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<VectorGenerator>()
		{
			Reflect<VectorGenerator>::Type(
				"VectorGenerator",

				Constructor(
					Overload()
				),

				Function(
					"Generate",
					Overload(
						Mutable,
						Returns<Vector3>()
					).Bind<VectorGenerator, &VectorGenerator::Generate>()
				)
			);
		}

		template <>
		void ReflectType<NumberRange>()
		{
			Reflect<NumberRange>::Type(
				"NumberRange",

				Member<Bind(&NumberRange::Min)>("Min"),
				Member<Bind(&NumberRange::Max)>("Max"),

				Constructor(
					Overload(),
					Overload(
						Argument<float>("min")
					),
					Overload(
						Argument<float>("min"),
						Argument<float>("max")
					)
				),

				Function(
					"rand",
					Overload(
						Mutable,
						Returns<float>()
					).Bind<NumberRange, &NumberRange::rand>()
				),

				Function(
					"Set",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<float>("min"),
						Argument<float>("max")
					).Bind<NumberRange, &NumberRange::Set>()
				)
			);
		}

		template <>
		void ReflectType<PointGenerator>()
		{
			Reflect<PointGenerator, VectorGenerator>::Type(
				"PointGenerator",

				Member<Bind(&PointGenerator::Position)>("Position"),

				Constructor(
					Overload(
						Argument<const Vector3&, Default(Vector3())>("position")
					)
				)
			);
		}

		template <>
		void ReflectType<UnitVectorGenerator>()
		{
			Reflect<UnitVectorGenerator, VectorGenerator>::Type(
				"UnitVectorGenerator",

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<ConeUnitVectorGenerator>()
		{
			Reflect<ConeUnitVectorGenerator, VectorGenerator>::Type(
				"ConeUnitVectorGenerator",

				Member<Bind(&ConeUnitVectorGenerator::Normal)>("Normal"),
				Member<Bind(&ConeUnitVectorGenerator::Angle)>("Angle"),

				Constructor(
					Overload()
				)
			);
		}
	}
}