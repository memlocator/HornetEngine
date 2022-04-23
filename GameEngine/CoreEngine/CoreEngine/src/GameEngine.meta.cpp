#include "GameEngine.h"

#include "GameWindow.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<GameEngine>()
		{
			Reflect<GameEngine, Object>::Class
			(
				"GameEngine",
				{ "GameObject" },

				Function(
					"GetPrimaryWindow",
					Overload(
						Const,
						Returns<std::shared_ptr<GraphicsEngine::GameWindow>>()
					).Bind<GameEngine, &GameEngine::GetPrimaryWindow>()
				),
				
				Function(
					"SetPrimaryWindow",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<GraphicsEngine::GameWindow>&>("primaryWindow")
					).Bind<GameEngine, &GameEngine::SetPrimaryWindow>()
				),

				Function(
					"GetArguments",
					Overload(
						Const,
						Returns<int>()
					).Bind<GameEngine, &GameEngine::GetArguments>()
				),

				Function(
					"GetArgument",
					Overload(
						Const,
						Returns<std::string>(),
						Argument<int>("index")
					).Bind<GameEngine, &GameEngine::GetArgument>()
				),

				Function(
					"HasArgumentFlag",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const std::string&>("name")
					).Bind<GameEngine, &GameEngine::HasArgumentFlag>()
				),

				Function(
					"GetArgumentValue",
					Overload(
						Const,
						Returns<std::string>(),
						Argument<const std::string&>("name")
					).Bind<GameEngine, &GameEngine::GetArgumentValue>()
				),

				Function(
					"SpawnProcess",
					Overload(
						Const,
						Returns<int>(),
						Argument<const std::string&>("scriptPath"),
						Argument<const ProcessArguments&>("arguments")
					).Bind<GameEngine, &GameEngine::SpawnProcess>()
				),

				Function(
					"CreateWindow",
					Overload(
						Const,
						Returns<std::shared_ptr<GraphicsEngine::GameWindow>>(),
						Argument<const std::string&>("name"),
						Argument<const std::string&>("title")
					).Bind<GameEngine, &GameEngine::CreateWindow>()
				),
				
				Function(
					"CreateConsole",
					Overload(
						Const,
						Returns<void>(),
						Argument<const std::string&>("name"),
						Argument<const std::string&>("title")
					).Bind<GameEngine, &GameEngine::CreateConsole>()
				)
			);
		}

		template <>
		void ReflectType<ProcessArguments>()
		{
			Reflect<ProcessArguments>::Type
			(
				"ProcessArguments",
				{ "GameObject" },

				Function(
					"GetArguments",
					Overload(
						Const,
						Returns<int>()
					).Bind<ProcessArguments, &ProcessArguments::GetArguments>()
				),

				Function(
					"GetArgument",
					Overload(
						Const,
						Returns<std::string>(),
						Argument<int>("index")
					).Bind<ProcessArguments, &ProcessArguments::GetArgument>()
				),

				Function(
					"HasArgumentFlag",
					Overload(
						Const,
						Returns<bool>(),
						Argument<const std::string&>("name")
					).Bind<ProcessArguments, &ProcessArguments::HasArgumentFlag>()
				),

				Function(
					"GetArgumentValue",
					Overload(
						Const,
						Returns<std::string>(),
						Argument<const std::string&>("name")
					).Bind<ProcessArguments, &ProcessArguments::GetArgumentValue>()
				),

				Function(
					"PushArgument",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("argument")
					).Bind<ProcessArguments, &ProcessArguments::PushArgument>()
				),

				Function(
					"InsertArgumentFlag",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("name")
					).Bind<ProcessArguments, &ProcessArguments::InsertArgumentFlag>()
				),

				Function(
					"InsertArgument",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("name"),
						Argument<const std::string&>("value")
					).Bind<ProcessArguments, &ProcessArguments::InsertArgument>()
				)
			);
		}
	}
}