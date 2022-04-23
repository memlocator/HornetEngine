#include "DrawSceneOperation.h"

#include "Scene.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<DrawSceneOperation>()
		{
			Reflect<DrawSceneOperation, RenderOperation>::Class
			(
				"DrawSceneOperation",
				{ "GameObject" },

				Member<Bind(&DrawSceneOperation::CurrentScene)>("CurrentScene"),

				Function(
					"Configure",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Scene>&>("scene")
					).Bind<DrawSceneOperation, &DrawSceneOperation::Configure>()
				)
			);
		}
	}
}