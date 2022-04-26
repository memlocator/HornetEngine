#include "InputSubscriber.h"

#include "LuaInput.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<InputSubscription>()
		{
			Reflect<InputSubscription, InputObject>::Class
			(
				"InputSubscription",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Function(
					"HasFocus",
					Overload(
						Const,
						Returns<bool>(),
						Argument<Enum::BoundDevice>("device")
					).Bind<InputSubscription, &InputSubscription::HasFocus>()
				),

				Function(
					"Subscribe",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Engine::InputObject>&>("device")
					).Bind<InputSubscription, &InputSubscription::Subscribe>()
				)
			);
		}

		template <>
		void ReflectType<InputSubscriber>()
		{
			Reflect<InputSubscriber, Object>::Class
			(
				"InputSubscriber",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Function(
					"HasFocus",
					Overload(
						Const,
						Returns<bool>(),
						Argument<Enum::BoundDevice>("device")
					).Bind<InputSubscriber, &InputSubscriber::HasFocus>()
				),

				Function(
					"Subscribe",
					Overload(
						Mutable,
						Returns<std::shared_ptr<InputSubscription>>(),
						Argument<const std::shared_ptr<Engine::InputObject>&>("device")
					).Bind<InputSubscriber, &InputSubscriber::Subscribe>()
				)
			);
		}
	}
}