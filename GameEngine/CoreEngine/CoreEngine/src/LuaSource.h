#pragma once

#include "Object.h"

namespace Engine
{
	class LuaSource : public Object
	{
	public:
		const std::string& GetPath() const;
		void LoadSource(const std::string& path);
		void SaveSource(const std::string& path);
		void SetSource(const std::string& source);
		const std::string& GetSource() const;
		int GetVersion() const;

	private:
		int Version = -1;
		std::string FileName;
		std::string Source;
	};
}
