#pragma once

#include "Object.h"

struct ScrollBarOrientationEnum
{
	enum ScrollBarOrientation
	{
		Vertical,
		Horizontal
	};
};

namespace Enum
{
	typedef ScrollBarOrientationEnum::ScrollBarOrientation ScrollBarOrientation;
}

namespace Engine
{
	class InputObject;
}

namespace GraphicsEngine
{
	class DeviceTransform;
	class ScreenCanvas;
	class InputSubscriber;
	class InputSubscription;

	class ScrollBar : public Engine::Object
	{
	public:
		void Initialize();
		void Update(float) {}


		const std::shared_ptr<DeviceTransform>& GetFrameTransform() const { return FrameTransform; }
		const std::shared_ptr<ScreenCanvas>& GetFrameCanvas() const { return FrameCanvas; }

		const std::shared_ptr<DeviceTransform>& GetBarTransform() const { return BarTransform; }
		const std::shared_ptr<ScreenCanvas>& GetBarCanvas() const { return BarCanvas; }

		void SetBarSize(float percent);
		void SetBarPercent(float percent);
		void SetBarOrientation(Enum::ScrollBarOrientation orientation);

		float GetBarSize() const { return BarSize; }
		float GetBarPercent() const { return BarPercent; }
		Enum::ScrollBarOrientation GetBarOrientation() const { return BarOrientation; }

	private:
		std::shared_ptr<DeviceTransform> FrameTransform;
		std::shared_ptr<ScreenCanvas> FrameCanvas;

		std::shared_ptr<DeviceTransform> BarTransform;
		std::shared_ptr<ScreenCanvas> BarCanvas;

		std::shared_ptr<GraphicsEngine::InputSubscriber> BarInputSubscriber;
		std::shared_ptr<Engine::InputObject> BarScrollInput;
		std::shared_ptr<Engine::InputObject> BarGrabInput;
		std::shared_ptr<Engine::InputObject> BarDragInput;

		float BarSize = 0.5f;
		float BarPercent = 0;
		Enum::ScrollBarOrientation BarOrientation = Enum::ScrollBarOrientation::Vertical;
		bool Updating = false;

		void UpdateBar();
		bool UpdateBarPosition();

		Instantiable;

		Inherits_Class(Object);

		Reflected(ScrollBar);
	};
}

namespace Engine
{
	Declare_Enum(ScrollBarOrientation);
}