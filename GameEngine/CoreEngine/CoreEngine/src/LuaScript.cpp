#include "LuaScript.h"

#include "Reflection/LuaThreadManager.h"
#include "LuaSource.h"
#include "Reflection/LuaTypeBinding.h"
#include <lua.hpp>

namespace Engine
{
	void LuaScript::Initialize()
	{
		Object::Initialize();

		SetTicks(true);
	}

	void LuaScript::Update(float delta)
	{
		Object::Update(delta);

		if (AutoRuns && Status == Enum::ScriptStatus::Uninitialized)
			Run();

		SetTicks(false);
	}

	LuaScript::~LuaScript()
	{
		if (Status != Enum::ScriptStatus::Dead)
			Stop();
	}

	std::shared_ptr<LuaSource> LuaScript::GetSource() const
	{
		return SourceObject.lock();
	}

	const std::string& LuaScript::GetSourceCode() const
	{
		return Source;
	}

	int LuaScript::GetVersion() const
	{
		return LoadedVersion;
	}

	bool LuaScript::UpToDate() const
	{
		if (!SourceChanged && Status == Enum::ScriptStatus::Running && !SourceObject.expired())
			return SourceObject.lock()->GetVersion() == LoadedVersion;

		return SourceChanged;
	}

	bool LuaScript::AutoRunEnabled() const
	{
		return AutoRuns;
	}

	Enum::ScriptStatus LuaScript::GetStatus() const
	{
		return Status;
	}

	void LuaScript::SetSource(const std::shared_ptr<LuaSource>& source)
	{
		Path = source->GetPath();
		SourceObject = source;
		Source = source->GetSource();
		LoadedVersion = source->GetVersion();

		SourceChanged = true;
	}

	void LuaScript::SetSource(const std::string& source)
	{
		Path = "source";
		Source = source;

		SourceChanged = true;
	}

	void LuaScript::SetAutoRun(bool mode)
	{
		AutoRuns = true;
	}

	void LuaScript::Run()
	{
		if (Status != ScriptStatus::Uninitialized)
			return;

		SourceChanged = false;
		ThreadID = Lua::Spawn(Source, GetFullName() + "[" + Path + "]",
			[this] (lua_State* lua) -> int
			{
				lua_pushstring(lua, "This");

				Engine::Lua::BindType<std::shared_ptr<Object>>::Push(lua, This.lock());

				lua_settable(lua, -3);

				return 0;
			},
			[this](ScriptStatus status)
			{
				Status = status;
			}
		);
	}

	void LuaScript::Stop()
	{
		if (Lua::Dead(ThreadID))
			return;

		Lua::Kill(ThreadID);

		ThreadID = -1;
	}

	void LuaScript::Reload()
	{
		Stop();

		if (!SourceObject.expired() && SourceObject.lock()->GetVersion() != LoadedVersion)
			SetSource(SourceObject.lock());

		Run();
	}

	int LuaScript::GetData(lua_State* lua)
	{
		return Lua::GetData(lua, ThreadID);
	}
}
