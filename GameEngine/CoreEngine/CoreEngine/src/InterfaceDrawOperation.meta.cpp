#include "InterfaceDrawOperation.h"

#include "DeviceTransform.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<InterfaceDrawOperation>()
		{
			Reflect<InterfaceDrawOperation, RenderOperation>::Class
			(
				"InterfaceDrawOperation",
				{ "GameObject" },

				Member<Bind(&InterfaceDrawOperation::CurrentScreen)>("CurrentScreen")
			);
		}
	}
}