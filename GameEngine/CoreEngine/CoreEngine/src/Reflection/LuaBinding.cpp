#include "LuaBinding.h"

const bool TestFunctions = true;

namespace Engine
{
	namespace Lua
	{
		void LuaBinding::BoundMember::Validate() const
		{
			if (Getter == nullptr || Setter == nullptr)
				throw "missing callback";

			if (TestFunctions)
			{
				Getter(nullptr);
				Setter(nullptr);
			}
		}

		void LuaBinding::BoundFunction::Validate() const
		{
			if (Callback == nullptr)
				throw "missing callback";

			if (TestFunctions)
				Callback(nullptr);
		}

		void LuaBinding::BoundEvent::Validate() const
		{
			if (Connect == nullptr || Disconnect == nullptr || Wait == nullptr)
				throw "missing callback";

			if (TestFunctions)
			{
				Connect(nullptr);
				Disconnect(nullptr);
				Wait(nullptr);
			}
		}

		void LuaBinding::BoundObject::Validate() const
		{
			if (Create == nullptr)
				throw "missing callback";

			if (TestFunctions)
				Create(nullptr);
		}

		lua_State* LuaBinder::GetGlobalLuaState()
		{
			return nullptr;
		}

		int LuaBinder::RegisterConnectedFunction(lua_State* lua)
		{
			return -1;
		}
	}
}