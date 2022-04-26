#include "ScrollBar.h"

#include "DeviceTransform.h"
#include "ScreenCanvas.h"
#include "InputSubscriber.h"
#include "InputContext.h"
#include "TaskScheduler.h"

namespace GraphicsEngine
{
	void ScrollBar::Initialize()
	{
		Engine::Object::Initialize();

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
		BarInputSubscriber->SetParent(BarTransform);

		FrameInputSubscriber = Engine::Create<InputSubscriber>();
		FrameInputSubscriber->SetParent(FrameTransform);

		SetTicks(true);
	}

	float GetAxis(const Vector3& vector, Enum::ScrollBarOrientation orientation)
	{
		if (orientation == Enum::ScrollBarOrientation::Horizontal)
			return vector.X;

		return vector.Y;
	}

	void ScrollBar::Update(float delta)
	{
		Engine::Object::Update(delta);

		if (!Initialized)
		{

			std::shared_ptr<InputContext> context = GetComponent<InputContext>();

			if (context == nullptr || context->InputSource.expired()) return;

			Initialized = true;

			std::shared_ptr<Engine::UserInput> inputSource = context->InputSource.lock();

			DefaultBarGrabInput = BarInputSubscriber->Subscribe(inputSource->GetInput(Enum::InputCode::MouseLeft));
			DefaultBarDragInput = inputSource->GetInput(Enum::InputCode::MousePosition);
			DefaultBarScrollInput = FrameInputSubscriber->Subscribe(inputSource->GetInput(Enum::InputCode::MouseWheel));

			if (BarScrollInput.expired())
				BarScrollInput = DefaultBarScrollInput;

			if (BarGrabInput.expired())
				BarGrabInput = DefaultBarGrabInput;

			if (BarDragInput.expired())
				BarDragInput = DefaultBarDragInput;
		}

		std::shared_ptr<Engine::InputObject> barScrollInput = BarScrollInput.lock();

		if (barScrollInput == nullptr)
			return;

		float scrollDelta = -barScrollInput->GetPosition().Y;

		if (scrollDelta == 0) return;

		float barSize = GetAxis(BarTransform->GetAbsoluteSize(), BarOrientation);
		float frameSize = GetAxis(FrameTransform->GetAbsoluteSize(), BarOrientation);

		if (std::abs(barSize - frameSize) > 1e-9f)
		{
			float movement = ScrollSpeed.Offset + ScrollSpeed.Scale * (ScrollRelativeToBar ? barSize : frameSize);
			
			SetBarPercent(BarPercent + scrollDelta * movement / (frameSize - barSize));
		}
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

	void ScrollBar::SetBarScrollInput(const std::shared_ptr<Engine::InputObject>& input)
	{

	}

	void ScrollBar::SetBarGrabInput(const std::shared_ptr<Engine::InputObject>& input)
	{
	}

	void ScrollBar::SetBarDragInput(const std::shared_ptr<Engine::InputObject>& input)
	{
	}

	bool ScrollBar::ConnectInput(std::weak_ptr<Engine::InputObject>& inputHandle, std::shared_ptr<Connection>& connection, const std::shared_ptr<Engine::InputObject> input)
	{
		if (inputHandle.lock() == input) return false;

		inputHandle = input;

		if (connection != nullptr)
		{
			connection->Disconnect();
			connection = nullptr;
		}

		if (input == nullptr) return false;

		connection = std::make_shared<Connection>();

		return true;
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