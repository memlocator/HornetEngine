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

		if (AutoRuns && GetStatus() == Enum::ScriptStatus::Idle)
			Run();

		//Enum::ScriptStatus status = GetStatus();
		//
		//if (status != Enum::ScriptStatus::Idle)
		//	Stop();

		SetTicks(false);
	}

	LuaScript::~LuaScript()
	{
		Enum::ScriptStatus status = GetStatus();

		if (status != Enum::ScriptStatus::Idle)
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
		if (!SourceChanged && GetStatus() == Enum::ScriptStatus::Running && !SourceObject.expired())
			return SourceObject.lock()->GetVersion() == LoadedVersion;

		return SourceChanged;
	}

	bool LuaScript::AutoRunEnabled() const
	{
		return AutoRuns;
	}

	Enum::ScriptStatus LuaScript::GetStatus() const
	{
		if (ThreadID == -1)
			return Enum::ScriptStatus::Idle;

		if (Lua::Running(ThreadID))
			return Enum::ScriptStatus::Running;

		if (Lua::Yielded(ThreadID))
			return Enum::ScriptStatus::Yielded;

		if (Lua::Dead(ThreadID))
			return Enum::ScriptStatus::Dead;

		return Enum::ScriptStatus::Idle;
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
		if (GetStatus() != Enum::ScriptStatus::Idle)
			return;

		SourceChanged = false;
		ThreadID = Lua::Spawn(Source, GetFullName() + "[" + Path + "]", [this] (lua_State* lua) -> int
		{
			lua_pushstring(lua, "This");

			Engine::Lua::BindType<std::shared_ptr<Object>>::Push(lua, This.lock());

			lua_settable(lua, -3);

			return 0;
		});
	}

	void LuaScript::Stop()
	{
		if (GetStatus() == Enum::ScriptStatus::Idle)
			return;

		Lua::Kill(ThreadID);

		ThreadID = -1;
	}

	void LuaScript::Reload()
	{
		Enum::ScriptStatus status = GetStatus();

		if (status == Enum::ScriptStatus::Running || status == Enum::ScriptStatus::Yielded)
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
