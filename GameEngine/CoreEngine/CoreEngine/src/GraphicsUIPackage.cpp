#include "GraphicsUIPackage.h"

#include "Alignment.h"
#include "Font.h"
#include "Appearance.h"
#include "Button.h"
#include "CanvasStencil.h"
#include "DeviceTransform.h"
#include "InputContext.h"
#include "InputSubscriber.h"
#include "ScreenCanvas.h"
#include "ScrollBar.h"
#include "Text.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		extern void ReflectType<Enum::ScrollBarOrientation>();

		template <>
		extern void ReflectType<GraphicsEngine::ScrollBar>();
		
		template <>
		extern void ReflectType<Enum::Alignment>();

		template <>
		extern void ReflectType<GraphicsEngine::Appearance>();

		template <>
		extern void ReflectType<GraphicsEngine::Button>();

		template <>
		extern void ReflectType<GraphicsEngine::CanvasStencil>();

		template <>
		extern void ReflectType<GraphicsEngine::DeviceTransform>();

		template <>
		extern void ReflectType<GraphicsEngine::InputContext>();

		template <>
		extern void ReflectType<GraphicsEngine::InputSubscription>();

		template <>
		extern void ReflectType<GraphicsEngine::InputSubscriber>();

		template <>
		extern void ReflectType<GraphicsEngine::ScreenCanvas>();

		template <>
		extern void ReflectType<GraphicsEngine::Text>();

		template <>
		extern void ReflectType<GraphicsEngine::Font>();

		template <>
		extern void ReflectType<GraphicsEngine::Font::Character>();

		template <>
		void ReflectPackage<GraphicsUIPackage>()
		{
			ReflectFromPackage<
				Enum::ScrollBarOrientation,
				GraphicsEngine::ScrollBar,
				Enum::Alignment,
				GraphicsEngine::Appearance,
				GraphicsEngine::Button,
				GraphicsEngine::CanvasStencil,
				GraphicsEngine::DeviceTransform,
				GraphicsEngine::InputContext,
				GraphicsEngine::InputSubscription,
				GraphicsEngine::InputSubscriber,
				GraphicsEngine::ScreenCanvas,
				GraphicsEngine::Text,
				GraphicsEngine::Font,
				GraphicsEngine::Font::Character
			>();
		}
	}
}