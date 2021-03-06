#pragma once

#include "IdentifierHeap.h"
#include "Object.h"
#include "Reflection/LuaThreadManager.h"

struct lua_State;

namespace Engine
{
	class LuaSource;

	class LuaScript : public Object
	{
	public:
		typedef Lua::ThreadStatus ScriptStatus;

		void Initialize();
		void Update(Float delta);

		~LuaScript();

		std::shared_ptr<LuaSource> GetSource() const;
		const std::string& GetSourceCode() const;
		int GetVersion() const;
		bool UpToDate() const;
		bool AutoRunEnabled() const;
		ScriptStatus GetStatus() const;
		void SetSource(const std::shared_ptr<LuaSource>& source);
		void SetSource(const std::string& source);
		void SetAutoRun(bool mode);
		void Run();
		void Stop();
		void Reload();
		int GetData(lua_State* lua);

	private:
		std::string Path;
		std::string Source;
		std::weak_ptr<LuaSource> SourceObject;
		int LoadedVersion = -1;
		int ThreadID = -1;
		bool SourceChanged = false;
		bool DataLoaded = false;
		bool AutoRuns = false;
		ScriptStatus Status = ScriptStatus::Uninitialized;
	};
}

namespace Enum
{
	typedef Engine::LuaScript::ScriptStatus ScriptStatus;
}
