#include "LuaScript.h"

#include <lua.hpp>

#include "LuaSource.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<LuaScript>()
		{
			Reflect<LuaScript, Object>::Class
			(
				"LuaScript",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Function(
					"GetSource",
					Overload(
						Const,
						Returns<std::shared_ptr<LuaSource>>()
					).Bind<LuaScript, &LuaScript::GetSource>()
				),

				Function(
					"GetSourceCode",
					Overload(
						Const,
						Returns<const std::string&>()
					).Bind<LuaScript, &LuaScript::GetSourceCode>()
				),

				Function(
					"GetVersion",
					Overload(
						Const,
						Returns<int>()
					).Bind<LuaScript, &LuaScript::GetVersion>()
				),

				Function(
					"UpToDate",
					Overload(
						Const,
						Returns<bool>()
					).Bind<LuaScript, &LuaScript::UpToDate>()
				),

				Function(
					"AutoRunEnabled",
					Overload(
						Const,
						Returns<bool>()
					).Bind<LuaScript, &LuaScript::AutoRunEnabled>()
				),

				Function(
					"GetStatus",
					Overload(
						Const,
						Returns<Enum::ScriptStatus>()
					).Bind<LuaScript, &LuaScript::GetStatus>()
				),

				Function(
					"SetSource",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<LuaSource>&>("source")
					).Bind<LuaScript, &LuaScript::SetSource>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("source")
					).Bind<LuaScript, &LuaScript::SetSource>()
				),

				Function(
					"SetAutoRun",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<bool>("mode")
					).Bind<LuaScript, &LuaScript::SetAutoRun>()
				),

				Function(
					"Run",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<LuaScript, &LuaScript::Run>()
				),

				Function(
					"Stop",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<LuaScript, &LuaScript::Stop>()
				),

				Function(
					"Reload",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<LuaScript, &LuaScript::Reload>()
				),

				Function(
					"GetData",
					LuaOverload<LuaScript, &LuaScript::GetData>()
				)
			);
		}

		template <>
		void ReflectType<Enum::ScriptStatus>()
		{
			Reflect<Enum::ScriptStatus>::Enum
			(
				"ScriptStatus",
				Value<Enum::ScriptStatus::Uninitialized>("Uninitialized"),
				Value<Enum::ScriptStatus::ParseError>("ParseError"),
				Value<Enum::ScriptStatus::Running>("Running"),
				Value<Enum::ScriptStatus::RuntimeError>("RuntimeError"),
				Value<Enum::ScriptStatus::Yielded>("Yielded"),
				Value<Enum::ScriptStatus::Finished>("Finished"),
				Value<Enum::ScriptStatus::Dead>("Dead")
			);
		}
	}
}