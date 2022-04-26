#include "SceneRayCastResults.h"

#include "Material.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<SceneRayCastResults>()
		{
			Reflect<SceneRayCastResults>::Type
			(
				"SceneRayCastResults",

				Member<Bind(&SceneRayCastResults::Distance)>("Distance"),
				Member<Bind(&SceneRayCastResults::Reflectivity)>("Reflectivity"),
				Member<Bind(&SceneRayCastResults::Intersection)>("Intersection"),
				Member<Bind(&SceneRayCastResults::Normal)>("Normal"),
				Member<Bind(&SceneRayCastResults::Color)>("Color"),
				Member<Bind(&SceneRayCastResults::GlowColor)>("GlowColor"),
				Member<Bind(&SceneRayCastResults::MaterialProperties)>("MaterialProperties"),
				Member<Bind(&SceneRayCastResults::Hit)>("Hit"),

				Constructor(
					Overload()
				),

				Function(
					"operator<",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const SceneRayCastResults&>("other")
					).Bind<SceneRayCastResults, &SceneRayCastResults::operator<>()
				),

				Function(
					"operator string",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<SceneRayCastResults, &SceneRayCastResults::operator std::string>()
				)
			);
		}
	}
}