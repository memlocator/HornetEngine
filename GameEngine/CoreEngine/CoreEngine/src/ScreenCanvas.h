#pragma once

#include "Appearance.h"

namespace GraphicsEngine
{
	class DeviceTransform;

	class ScreenCanvas : public Engine::Object
	{
	public:
		bool Visible = true;
		std::weak_ptr<Appearance> Appearance;

		~ScreenCanvas() {}

		void Draw();
		
	private:
		void DrawScreen(const std::shared_ptr<DeviceTransform>& transform);
	};
}
