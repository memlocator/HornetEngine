#include "LuaJson.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <lua.hpp>

#include "Reflection/LuaError.h"

namespace Engine
{
	struct LuaJsonData
	{
		lua_State* Lua = nullptr;
		std::vector<int> TableIndices;
	};

	std::string Desanitize(const std::string& input)
	{
		std::string output;

		output.reserve(input.size() + 1);

		bool escaped = false;

		for (int i = 0; i < int(input.size()); ++i)
		{
			if (input[i] == '\\' && !escaped)
			{
				escaped = true;

				continue;
			}
			
			escaped = false;

			output.push_back(input[i]);
		}

		return output;
	}

	int DecodeJson(lua_State* lua)
	{
		int top = lua_gettop(lua);

		int arg1Type = lua_type(lua, 1);
		int arg2Type = lua_type(lua, 2);

		if (top < 1 || arg1Type != LUA_TSTRING)
			LuaError(lua, "bad argument to #1: expected 'string'");

		if (top >= 2 && arg2Type != LUA_TBOOLEAN && arg2Type != LUA_TNIL)
			LuaError(lua, "bad argument to #2: expected 'boolean'");

		std::string input = lua_tostring(lua, 1);
		bool isPath = false;

		if (top >= 2 && arg2Type == LUA_TBOOLEAN)
			isPath = lua_toboolean(lua, 2);

		LuaJsonData data = {
			lua
		};

		try
		{
			JsonParser parser(input, isPath);

			parser.ReadKey = [&data](const std::string& key)
			{
				lua_pushstring(data.Lua, Desanitize(key).c_str());
			};

			parser.ReadIndex = [&data](int index)
			{
				lua_pushnumber(data.Lua, lua_Number(index + 1));
			};

			parser.ReadNumber = [&data](float value, char modifier)
			{
				lua_pushnumber(data.Lua, lua_Number(value));
				lua_settable(data.Lua, data.TableIndices[data.TableIndices.size() - 1]);
			};

			parser.ReadString = [&data](const std::string& value)
			{
				lua_pushstring(data.Lua, Desanitize(value).c_str());
				lua_settable(data.Lua, data.TableIndices[data.TableIndices.size() - 1]);
			};

			parser.ReadBool = [&data](bool value)
			{
				lua_pushboolean(data.Lua, value);
				lua_settable(data.Lua, data.TableIndices[data.TableIndices.size() - 1]);
			};

			parser.PushContainer = [&data](bool value)
			{
				lua_createtable(data.Lua, 0, 0);

				data.TableIndices.push_back(lua_gettop(data.Lua));
			};

			parser.PopContainer = [&data]()
			{
				data.TableIndices.pop_back();

				if (data.TableIndices.size() > 0)
					lua_settable(data.Lua, data.TableIndices[data.TableIndices.size() - 1]);
			};

			try
			{
				parser.Parse();
			}
			catch (std::string& error)
			{
				lua_pushnil(lua);
				lua_pushstring(lua, error.c_str());

				return 2;
			}
		}
		catch (JsonParserException e)
		{
			lua_pushnil(lua);
			lua_pushstring(lua, e.what());

			return 2;
		}

		return 1;
	}

	class LuaJsonEncoder
	{
	public:
		struct TableInfo
		{
			int Index = 0;
			bool IsArray = false;
		};

		lua_State* lua = nullptr;
		int StackIndex = 0;
		std::stringstream Output;
		int StackDepth = 0;
		char Buffer[2048];

		void Encode()
		{
			PushTable(StackIndex);

			NextLine(false);
		}

		void NextLine(bool comma)
		{
			if (comma)
				Output << ",";

			Output << std::endl;

			for (int i = 0; i < StackDepth; ++i)
				Output << '\t';
		}

		void PushTable(int index)
		{
			int tableLength = int(lua_rawlen(lua, index));

			if (tableLength == 0)
			{
				lua_pushinteger(lua, 0);
				lua_gettable(lua, index);

				if (lua_isnil(lua, -1))
					tableLength = -1;

				lua_pop(lua, 1);
			}

			++StackDepth;

			if (tableLength == -1)
				Output << '{';
			else
				Output << '[';

			if (tableLength != 0)
				Iterate(index, tableLength != -1);

			--StackDepth;

			NextLine(false);

			if (tableLength == -1)
				Output << '}';
			else
				Output << ']';
		}

		void Sanitize(const std::string& input)
		{
			Output << '"';

			for (int i = 0; i < int(input.size()); i)
			{
				int length;

				for (length = 0; i + length < int(input.size()) && input[i + length] != '"' && input[i + length] != '\\'; ++length);

				if (length > 0)
					Output << input.substr(i, length);

				i += length;

				while (i < int(input.size()) && (input[i] == '\\' || input[i] == '"'))
				{
					Output << '\\' << input[i];

					++i;
				}
			}

			Output << '"';
		}

		void PushValue(int type)
		{
			std::string keyType;
			std::string value;

			switch (type)
			{
			case LUA_TSTRING:
				Sanitize(lua_tostring(lua, -1));

				break;

			case LUA_TBOOLEAN:
				Output << lua_toboolean(lua, -1);

				break;

			case LUA_TNUMBER:
				Output << float(lua_tonumber(lua, -1));

				break;

			default:
				std::string value = lua_tolstring(lua, -1, 0);

				LuaError(lua, "json.encode - Attempt to encode an unsupported value. Failed on value '%s'", value.c_str());
			}
		}

		void Iterate(int index, bool isArray)
		{
			lua_pushnil(lua);

			bool firstIteration = true;

			while (lua_next(lua, index) != 0)
			{
				NextLine(!firstIteration);

				int keyType = lua_type(lua, -2);
				int valueType = lua_type(lua, -1);

				if (isArray)
				{
					if (keyType != LUA_TNUMBER)
					{
						std::string value = lua_tolstring(lua, -2, 0);

						LuaError(lua, "json.encode - Attempt to encode a mixed index table. Failed on key '%s'", value.c_str());
					}
				}
				else
				{
					if (keyType != LUA_TSTRING)
					{
						std::string value = lua_tolstring(lua, -2, 0);

						LuaError(lua, "json.encode - Attempt to encode a mixed index table. Failed on key '%s'", value.c_str());
					}

					Sanitize(lua_tostring(lua, -2));

					Output << " : ";
				}

				if (valueType == LUA_TTABLE)
					PushTable(lua_gettop(lua));
				else
					PushValue(valueType);

				lua_pop(lua, 1);

				firstIteration = false;
			}
		}
	};

	int EncodeJson(lua_State* lua)
	{
		int top = lua_gettop(lua);

		int arg1Type = lua_type(lua, 1);
		int arg2Type = lua_type(lua, 2);

		if (top < 1 || arg1Type != LUA_TTABLE)
			LuaError(lua, "bad argument to #1: expected 'string'");

		if (top >= 2 && arg2Type != LUA_TSTRING && arg2Type != LUA_TNIL)
			LuaError(lua, "bad argument to #1: expected 'boolean'");

		std::string path;

		if (top >= 2)
			path = lua_tostring(lua, 2);

		lua_pushvalue(lua, 1);

		LuaJsonEncoder encoder = {
			lua,
			lua_gettop(lua)
		};

		encoder.Encode();

		if (path != "")
		{
			std::ofstream out(path, std::ios_base::out);

			if (!out.good())
			{
				LuaError(lua, "json.encode - failed to open output file at directory '%s'", path.c_str());
			}

			out << encoder.Output.str();

			out.flush();
		}

		lua_pushstring(lua, encoder.Output.str().c_str());

		return 1;
	}

	const luaL_Reg LuaJsonLib[3] = {
		{ "decode", DecodeJson },
		{ "encode", EncodeJson },
		{ 0, 0 }
	};
}
