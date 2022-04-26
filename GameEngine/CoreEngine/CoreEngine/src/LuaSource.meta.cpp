#include "LuaSource.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<LuaSource>()
		{
			Reflect<LuaSource, Object>::Class
			(
				"LuaSource",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Function(
					"GetPath",
					Overload(
						Const,
						Returns<const std::string&>()
					).Bind<LuaSource, &LuaSource::GetPath>()
				),

				Function(
					"LoadSource",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("path")
					).Bind<LuaSource, &LuaSource::LoadSource>()
				),

				Function(
					"LoadSource",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("path")
					).Bind<LuaSource, &LuaSource::LoadSource>()
				),

				Function(
					"SaveSource",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("path")
					).Bind<LuaSource, &LuaSource::SaveSource>()
				),

				Function(
					"SetSource",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("source")
					).Bind<LuaSource, &LuaSource::SetSource>()
				),

				Function(
					"GetSource",
					Overload(
						Const,
						Returns<const std::string&>()
					).Bind<LuaSource, &LuaSource::GetSource>()
				),

				Function(
					"GetVersion",
					Overload(
						Const,
						Returns<int>()
					).Bind<LuaSource, &LuaSource::GetVersion>()
				)
			);
		}
	}
}