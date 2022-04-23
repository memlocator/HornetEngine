#include "InputContext.h"

#include "LuaInput.h"
#include "InputSubscriber.h"
#include "DeviceTransform.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<InputContext>()
		{
			Reflect<InputContext, Object>::Class
			(
				"InputContext",
				{ "GameObject" },

				Member<Bind(&InputContext::Enabled)>("Enabled"),
				Member<Bind(&InputContext::Device)>("Device"),
				Member<Bind(&InputContext::InputSource)>("InputSource"),

				Function(
					"GetFocus",
					Overload(
						Const,
						Returns<std::shared_ptr<InputSubscriber>>(),
						Argument<Enum::BoundDevice>("device")
					).Bind<InputContext, &InputContext::GetFocus>()
				)
			);
		}
	}
}