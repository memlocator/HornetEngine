#include "ScrollBar.h"

#include "DeviceTransform.h"
#include "ScreenCanvas.h"
#include "InputSubscriber.h"

namespace GraphicsEngine
{
	void ScrollBar::Initialize()
	{
		FrameTransform = Engine::Create<DeviceTransform>();
		FrameTransform->SetParent(This.lock());
		FrameTransform->Name = "FrameTransform";

		FrameCanvas = Engine::Create<ScreenCanvas>();
		FrameCanvas->SetParent(FrameTransform);
		FrameCanvas->Name = "FrameCanvas";

		BarTransform = Engine::Create<DeviceTransform>();
		BarTransform->SetParent(FrameTransform);
		BarTransform->Name = "BarTransform";

		BarCanvas = Engine::Create<ScreenCanvas>();
		BarCanvas->SetParent(BarTransform);
		BarCanvas->Name = "BarCanvas";

		UpdateBar();

		FrameTransform->TransformChanged.Connect(std::bind(&ScrollBar::UpdateBarPosition, this));
		BarTransform->TransformChanged.Connect(std::bind(&ScrollBar::UpdateBarPosition, this));

		BarInputSubscriber = Engine::Create<InputSubscriber>();
		BarInputSubscriber->SetParent(This.lock());


	}

	void ScrollBar::SetBarSize(float percent)
	{
		BarSize = std::max(std::min(1.f, percent), 0.f);

		UpdateBar();
	}

	void ScrollBar::SetBarPercent(float percent)
	{
		BarPercent = std::max(std::min(1.f, percent), 0.f);

		UpdateBar();
	}

	void ScrollBar::SetBarOrientation(Enum::ScrollBarOrientation orientation)
	{
		BarOrientation = orientation;

		UpdateBar();
	}

	void ScrollBar::UpdateBar()
	{
		Updating = true;

		if (BarOrientation == Enum::ScrollBarOrientation::Vertical)
		{
			BarTransform->Size = DeviceVector(1, 0, BarSize, 0);
			BarTransform->Position.X = DeviceAxis(0, 0);
			BarTransform->Position.Y = DeviceAxis((1 - BarSize) * BarPercent, 0);
		}
		else
		{
			BarTransform->Size = DeviceVector(BarSize, 0, 1, 0);
			BarTransform->Position.X = DeviceAxis((1 - BarSize) * BarPercent, 0);
			BarTransform->Position.Y = DeviceAxis(0, 0);
		}

		Updating = false;
	}

	bool ScrollBar::UpdateBarPosition()
	{
		if (Updating) return true;

		Updating = true;

		float absSize = 0;
		DeviceAxis axis;

		if (BarOrientation == Enum::ScrollBarOrientation::Vertical)
		{
			absSize = BarTransform->GetAbsoluteSize().Y;
			axis = BarTransform->Position.Y;
		}
		else
		{
			absSize = BarTransform->GetAbsoluteSize().X;
			axis = BarTransform->Position.X;
		}

		if (absSize == 0)
			absSize = 1;

		float position = std::min(std::max(axis.Scale + axis.Offset / absSize, 0.f), 1.f);
		float barSize = 1 - BarSize;

		if (barSize == 0)
			barSize = 1;

		BarPercent = position / barSize;

		UpdateBar();

		Updating = false;

		return true;
	}
}