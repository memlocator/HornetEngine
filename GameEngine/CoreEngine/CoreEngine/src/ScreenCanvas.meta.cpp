#include "ScreenCanvas.h"

#include "Appearance.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<ScreenCanvas>()
		{
			Reflect<ScreenCanvas, Object>::Class
			(
				"ScreenCanvas",
				{ "GameObject" },

				Member<Bind(&ScreenCanvas::Visible)>("Visible"),
				Member<Bind(&ScreenCanvas::Appearance)>("Appearance")
			);
		}
	}
}