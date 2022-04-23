#include "Button.h"

#include "Appearance.h"
#include "InputSubscriber.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Button>()
		{
			Reflect<Button, Object>::Class
			(
				"Button",
				{ "GameObject" },

				Member<Bind(&Button::Hover)>("Hover"),
				Member<Bind(&Button::Pressed)>("Pressed"),
				Member<Bind(&Button::Idle)>("Idle"),
				Member<Bind(&Button::Binding)>("Binding"),
				Member<Bind(&Button::Device)>("Device")
			);
		}
	}
}