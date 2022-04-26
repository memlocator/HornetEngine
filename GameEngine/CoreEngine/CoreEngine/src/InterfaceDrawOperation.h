#pragma once

#include "RenderOperation.h"
#include "DeviceTransform.h"

namespace GraphicsEngine
{
	class InterfaceDrawOperation : public RenderOperation
	{
	public:
		std::weak_ptr<DeviceTransform> CurrentScreen;

		void Render();
	};
}
