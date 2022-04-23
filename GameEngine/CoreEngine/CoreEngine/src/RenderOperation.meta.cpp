#include "RenderOperation.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<RenderOperation>()
		{
			Reflect<RenderOperation, Object>::Class
			(
				"RenderOperation",
				{ "GameObject" },

				Member<Bind(&RenderOperation::RenderAutomatically)>("RenderAutomatically"),

				Function(
					"Render",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<RenderOperation, &RenderOperation::Render>()
				)
			);
		}
	}
}