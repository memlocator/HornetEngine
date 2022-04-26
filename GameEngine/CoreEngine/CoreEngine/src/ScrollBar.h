#pragma once

#include "Object.h"
#include "TaskScheduler.h"
#include "DeviceVector.h"

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
		void Update(float);

		bool ScrollRelativeToBar = true;
		DeviceAxis ScrollSpeed = DeviceAxis(0.1f, 0);

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

		void SetBarScrollInput(const std::shared_ptr<Engine::InputObject>& input);
		void SetBarGrabInput(const std::shared_ptr<Engine::InputObject>& input);
		void SetBarDragInput(const std::shared_ptr<Engine::InputObject>& input);

		const std::weak_ptr<Engine::InputObject>& GetBarScrollInput() const { return BarScrollInput; }
		const std::weak_ptr<Engine::InputObject>& GetBarGrabInput() const { return BarGrabInput; }
		const std::weak_ptr<Engine::InputObject>& GetBarDragInput() const { return BarDragInput; }

	private:
		std::shared_ptr<DeviceTransform> FrameTransform;
		std::shared_ptr<ScreenCanvas> FrameCanvas;

		std::shared_ptr<DeviceTransform> BarTransform;
		std::shared_ptr<ScreenCanvas> BarCanvas;

		std::shared_ptr<GraphicsEngine::InputSubscriber> BarInputSubscriber;
		std::shared_ptr<GraphicsEngine::InputSubscriber> FrameInputSubscriber;

		std::weak_ptr<Engine::InputObject> BarScrollInput;
		std::weak_ptr<Engine::InputObject> BarGrabInput;
		std::weak_ptr<Engine::InputObject> BarDragInput;

		std::shared_ptr<Engine::InputObject> DefaultBarScrollInput;
		std::shared_ptr<Engine::InputObject> DefaultBarGrabInput;
		std::shared_ptr<Engine::InputObject> DefaultBarDragInput;

		float BarSize = 0.5f;
		float BarPercent = 0;
		Enum::ScrollBarOrientation BarOrientation = Enum::ScrollBarOrientation::Vertical;
		bool Updating = false;
		bool Initialized = false;
		
		bool ConnectInput(std::weak_ptr<Engine::InputObject>& inputHandle, std::shared_ptr<Connection>& connection, const std::shared_ptr<Engine::InputObject> input);

		void UpdateBar();
		bool UpdateBarPosition();
	};
}