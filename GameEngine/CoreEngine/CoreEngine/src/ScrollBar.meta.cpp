#include "ScrollBar.h"

#include "DeviceTransform.h"
#include "ScreenCanvas.h"
#include "LuaInput.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Enum::ScrollBarOrientation>()
		{
			Reflect<Enum::ScrollBarOrientation>::Enum
			(
				"ScrollBarOrientation",
				Value<Enum::ScrollBarOrientation::Vertical>("Vertical"),
				Value<Enum::ScrollBarOrientation::Horizontal>("Horizontal")
			);
		}

		template <>
		void ReflectType<ScrollBar>()
		{
			Reflect<ScrollBar, Object>::Class
			(
				"ScrollBar",
				{ "GameObject" },

				Property(
					"FrameTransform",
					Getter<const std::shared_ptr<DeviceTransform>&>(Const).Bind<ScrollBar, &ScrollBar::GetFrameTransform>()
				),

				Property(
					"FrameCanvas",
					Getter<const std::shared_ptr<ScreenCanvas>&>(Const).Bind<ScrollBar, &ScrollBar::GetFrameCanvas>()
				),

				Property(
					"BarTransform",
					Getter<const std::shared_ptr<DeviceTransform>&>(Const).Bind<ScrollBar, &ScrollBar::GetBarTransform>()
				),

				Property(
					"BarCanvas",
					Getter<const std::shared_ptr<ScreenCanvas>&>(Const).Bind<ScrollBar, &ScrollBar::GetBarCanvas>()
				),

				Property(
					"BarSize",
					Getter<Float>(Const).Bind<ScrollBar, &ScrollBar::GetBarSize>(),
					Setter<Float>(Mutable).Bind<ScrollBar, &ScrollBar::SetBarSize>()
				),

				Property(
					"BarPercent",
					Getter<Float>(Const).Bind<ScrollBar, &ScrollBar::GetBarPercent>(),
					Setter<Float>(Mutable).Bind<ScrollBar, &ScrollBar::SetBarPercent>()
				),

				Property(
					"BarOrientation",
					Getter<Enum::ScrollBarOrientation>(Const).Bind<ScrollBar, &ScrollBar::GetBarOrientation>(),
					Setter<Enum::ScrollBarOrientation>(Mutable).Bind<ScrollBar, &ScrollBar::SetBarOrientation>()
				),

				Constructor(
					Overload()
				),

				Function(
					"GetFrameTransform",
					Overload(
						Const,
						Returns<const std::shared_ptr<DeviceTransform>&>()
					).Bind<ScrollBar, &ScrollBar::GetFrameTransform>()
				),

				Function(
					"GetFrameCanvas",
					Overload(
						Const,
						Returns<const std::shared_ptr<ScreenCanvas>&>()
					).Bind<ScrollBar, &ScrollBar::GetFrameCanvas>()
				),

				Function(
					"GetBarTransform",
					Overload(
						Const,
						Returns<const std::shared_ptr<DeviceTransform>&>()
					).Bind<ScrollBar, &ScrollBar::GetBarTransform>()
				),

				Function(
					"GetBarCanvas",
					Overload(
						Const,
						Returns<const std::shared_ptr<ScreenCanvas>&>()
					).Bind<ScrollBar, &ScrollBar::GetBarCanvas>()
				),

				Function(
					"SetBarSize",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<Float>("percent")
					).Bind<ScrollBar, &ScrollBar::SetBarSize>()
				),

				Function(
					"SetBarPercent",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<Float>("percent")
					).Bind<ScrollBar, &ScrollBar::SetBarPercent>()
				),

				Function(
					"SetBarOrientation",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<Enum::ScrollBarOrientation>("orientation")
					).Bind<ScrollBar, &ScrollBar::SetBarOrientation>()
				),

				Function(
					"GetBarSize",
					Overload(
						Const,
						Returns<Float>()
					).Bind<ScrollBar, &ScrollBar::GetBarSize>()
				),

				Function(
					"GetBarPercent",
					Overload(
						Const,
						Returns<Float>()
					).Bind<ScrollBar, &ScrollBar::GetBarPercent>()
				),

				Function(
					"GetBarOrientation",
					Overload(
						Const,
						Returns<Enum::ScrollBarOrientation>()
					).Bind<ScrollBar, &ScrollBar::GetBarOrientation>()
				),

				Function(
					"SetBarScrollInput",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Engine::InputObject>&>("input")
					).Bind<ScrollBar, &ScrollBar::SetBarScrollInput>()
				),

				Function(
					"SetBarGrabInput",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Engine::InputObject>&>("input")
					).Bind<ScrollBar, &ScrollBar::SetBarGrabInput>()
				),

				Function(
					"SetBarDragInput",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Engine::InputObject>&>("input")
					).Bind<ScrollBar, &ScrollBar::SetBarDragInput>()
				),

				Function(
					"GetBarScrollInput",
					Overload(
						Const,
						Returns<const std::weak_ptr<Engine::InputObject>&>()
					).Bind<ScrollBar, &ScrollBar::GetBarScrollInput>()
				),

				Function(
					"GetBarGrabInput",
					Overload(
						Const,
						Returns<const std::weak_ptr<Engine::InputObject>&>()
					).Bind<ScrollBar, &ScrollBar::GetBarGrabInput>()
				),

				Function(
					"GetBarDragInput",
					Overload(
						Const,
						Returns<const std::weak_ptr<Engine::InputObject>&>()
					).Bind<ScrollBar, &ScrollBar::GetBarDragInput>()
				)
			);
		}
	}
}