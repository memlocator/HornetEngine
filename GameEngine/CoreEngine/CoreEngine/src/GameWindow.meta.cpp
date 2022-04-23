#include "GameWindow.h"

#include "LuaInput.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<GameWindow>()
		{
			Reflect<GameWindow, Object>::Class
			(
				"GameWindow",
				{ "GameObject" },

				Function(
					"GetInput",
					Overload(
						Const,
						Returns<std::shared_ptr<Engine::UserInput>>()
					).Bind<GameWindow, &GameWindow::GetInput>()
				),

				Function(
					"GetRefreshRate",
					Overload(
						Mutable,
						Returns<int>()
					).Bind<GameWindow, &GameWindow::GetRefreshRate>()
				),

				Function(
					"GetResolution",
					Overload(
						Mutable,
						Returns<Vector3>()
					).Bind<GameWindow, &GameWindow::GetResolution>()
				),

				Function(
					"SetMousePosition",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("position")
					).Bind<GameWindow, &GameWindow::SetMousePosition>()
				)
			);
		}
	}
}