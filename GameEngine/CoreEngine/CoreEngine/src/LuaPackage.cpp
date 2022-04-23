#include "LuaPackage.h"

#include "LuaScript.h"
#include "LuaSource.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		extern void ReflectType<LuaScript>();

		template <>
		extern void ReflectType<LuaSource>();

		template <>
		extern void ReflectType<Enum::ScriptStatus>();

		template <>
		void ReflectPackage<LuaPackage>()
		{
			ReflectFromPackage<
				LuaScript,
				LuaSource,
				Enum::ScriptStatus
			>();
		}
	}
}