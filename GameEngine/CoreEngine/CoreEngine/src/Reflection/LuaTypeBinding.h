#pragma once

#include <lua.hpp>
#include <string>
#include <memory>

#include "BoundObject.h"
#include "../Object.h"
#include "Reflected.h"

namespace Engine
{
	namespace Lua
	{
		void MakeBinding(lua_State* lua, int id);

		template <typename Type>
		struct BoundTypeAllocators
		{
			static inline IDHeap<Type> AllocatedData;
		};

		template <typename Type>
		struct BindType;

		template <>
		struct BindType<void>
		{
			static inline const int Returns = 0;
		};

		template <>
		struct BindType<bool>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, bool value)
			{
				lua_pushboolean(lua, (int)value);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static bool Pop(lua_State* lua, int index)
				{
					return (bool)lua_toboolean(lua, index);
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static bool Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return (bool)lua_toboolean(lua, index);
				}
			};
		};

		template <>
		struct BindType<unsigned char>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, unsigned char value)
			{
				lua_pushinteger(lua, (lua_Integer)value);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static unsigned char Pop(lua_State* lua, int index)
				{
					return (unsigned char)lua_tointeger(lua, index);
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static unsigned char Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return (unsigned char)lua_tointeger(lua, index);
				}
			};
		};

		template <>
		struct BindType<signed char>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, signed char value)
			{
				lua_pushinteger(lua, (lua_Integer)value);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static signed char Pop(lua_State* lua, int index)
				{
					return (signed char)lua_tointeger(lua, index);
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static signed char Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return (signed char)lua_tointeger(lua, index);
				}
			};
		};

		template <>
		struct BindType<unsigned short>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, unsigned short value)
			{
				lua_pushinteger(lua, (lua_Integer)value);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static unsigned short Pop(lua_State* lua, int index)
				{
					return (unsigned short)lua_tointeger(lua, index);
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static unsigned short Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return (unsigned short)lua_tointeger(lua, index);
				}
			};
		};

		template <>
		struct BindType<short>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, short value)
			{
				lua_pushinteger(lua, (lua_Integer)value);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static short Pop(lua_State* lua, int index)
				{
					return (short)lua_tointeger(lua, index);
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static short Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return (short)lua_tointeger(lua, index);
				}
			};
		};

		template <>
		struct BindType<unsigned int>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, unsigned int value)
			{
				lua_pushinteger(lua, (lua_Integer)value);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static unsigned int Pop(lua_State* lua, int index)
				{
					return (unsigned int)lua_tointeger(lua, index);
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static unsigned int Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return (unsigned int)lua_tointeger(lua, index);
				}
			};
		};

		template <>
		struct BindType<int>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, int value)
			{
				lua_pushinteger(lua, (lua_Integer)value);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static int Pop(lua_State* lua, int index)
				{
					return (int)lua_tointeger(lua, index);
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static int Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return (int)lua_tointeger(lua, index);
				}
			};
		};

		template <>
		struct BindType<unsigned long long>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, unsigned long long value)
			{
				lua_pushinteger(lua, (lua_Integer)value);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static unsigned long long Pop(lua_State* lua, int index)
				{
					return (unsigned long long)lua_tointeger(lua, index);
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static unsigned long long Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return (unsigned long long)lua_tointeger(lua, index);
				}
			};
		};

		template <>
		struct BindType<long long>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, long long value)
			{
				lua_pushinteger(lua, (lua_Integer)value);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static int Pop(lua_State* lua, int index)
				{
					return (long long)lua_tointeger(lua, index);
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static int Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return (long long)lua_tointeger(lua, index);
				}
			};
		};

		template <>
		struct BindType<float>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, float value)
			{
				lua_pushnumber(lua, (lua_Number)value);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static float Pop(lua_State* lua, int index)
				{
					return (float)lua_tonumber(lua, index);
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static float Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return (float)lua_tonumber(lua, index);
				}
			};
		};

		template <>
		struct BindType<double>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, double value)
			{
				lua_pushnumber(lua, (lua_Number)value);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static float Pop(lua_State* lua, int index)
				{
					return (double)lua_tonumber(lua, index);
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static float Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return (double)lua_tonumber(lua, index);
				}
			};
		};

		template <>
		struct BindType<std::string>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, const std::string& value)
			{
				lua_pushlstring(lua, value.c_str(), value.size());
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static std::string Pop(lua_State* lua, int index)
				{
					return std::string(lua_tostring(lua, index));
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static std::string Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return std::string(lua_tostring(lua, index));
				}
			};
		};

		template <>
		struct BindType<const char*>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, const char* value)
			{
				lua_pushstring(lua, value);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static const char* Pop(lua_State* lua, int index)
				{
					return lua_tostring(lua, index);
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static const char* Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					return lua_tostring(lua, index);
				}
			};
		};

		template <typename Type>
		struct BindType<std::shared_ptr<Type>>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, const std::shared_ptr<Type>& value)
			{
				if (value == nullptr)
				{
					lua_pushnil(lua);

					return;
				}

				std::pair<int, BoundObject*> bound = BoundObject::Allocate();

				bound.second->GameObject = value;
				bound.second->ObjectType = LuaObjectType::Object;
				bound.second->Type = Meta::Reflected<Type>::GetMeta();

				MakeBinding(lua, bound.first);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static std::shared_ptr<Type> Pop(lua_State* lua, int index)
				{
					int reference = (int)(intptr_t)lua_touserdata(lua, index);
					BoundObject& bound = BoundObject::GetBound(reference);

					return bound.GameObject->Cast<Type>();
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static std::shared_ptr<Type> Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					int reference = (int)(intptr_t)lua_touserdata(lua, index);
					BoundObject& bound = BoundObject::GetBound(reference);

					return bound.GameObject->Cast<Type>();
				}
			};
		};

		template <typename Type>
		struct BindType<std::weak_ptr<Type>>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, const std::weak_ptr<Type>& value)
			{
				if (value.expired())
				{
					lua_pushnil(lua);

					return;
				}

				std::pair<int, BoundObject*> bound = BoundObject::Allocate();

				bound.second->GameObject = value.lock();
				bound.second->ObjectType = LuaObjectType::Object;
				bound.second->Type = Meta::Reflected<Type>::GetMeta();

				MakeBinding(lua, bound.first);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static std::weak_ptr<Type> Pop(lua_State* lua, int index)
				{
					int reference = (int)(intptr_t)lua_touserdata(lua, index);
					BoundObject& bound = BoundObject::GetBound(reference);

					return bound.GameObject->Cast<Type>();
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static std::weak_ptr<Type> Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					int reference = (int)(intptr_t)lua_touserdata(lua, index);
					BoundObject& bound = BoundObject::GetBound(reference);

					return bound.GameObject->Cast<Type>();
				}
			};
		};

		template <typename Type>
		struct BindType<Type*>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, Type* value)
			{
				if (value == nullptr)
				{
					lua_pushnil(lua);

					return;
				}

				std::pair<int, BoundObject*> bound = BoundObject::Allocate();

				bound.second->GameObject = value->This.lock()->Cast<Type>();
				bound.second->ObjectType = LuaObjectType::Object;
				bound.second->Type = Meta::Reflected<Type>::GetMeta();

				MakeBinding(lua, bound.first);
			}

			static void Push(lua_State* lua, const Type* value)
			{
				if (value == nullptr)
				{
					lua_pushnil(lua);

					return;
				}

				std::pair<int, BoundObject*> bound = BoundObject::Allocate();

				bound.second->GameObject = value->This.lock()->Cast<Type>();
				bound.second->ObjectType = LuaObjectType::Object;

				MakeBinding(lua, bound.first);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static Type* Pop(lua_State* lua, int index)
				{
					int reference = (int)(intptr_t)lua_touserdata(lua, index);
					BoundObject& bound = BoundObject::GetBound(reference);

					return bound.GameObject->Cast<Type>().get();
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static Type* Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					int reference = (int)(intptr_t)lua_touserdata(lua, index);
					BoundObject& bound = BoundObject::GetBound(reference);

					return bound.GameObject->Cast<Type>().get();
				}
			};
		};

		template <typename Type>
		concept EnumType = std::is_enum_v<Type>;

		template <EnumType Type>
		struct BindType<Type>
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, Type value)
			{
				std::pair<int, BoundObject*> bound = BoundObject::Allocate();

				bound.second->DataId = (int)value;
				bound.second->ObjectType = LuaObjectType::Enum;
				bound.second->Type = Meta::Reflected<Type>::GetMeta();

				MakeBinding(lua, bound.first);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static Type Pop(lua_State* lua, int index)
				{
					int reference = (int)(intptr_t)lua_touserdata(lua, index);
					BoundObject& bound = BoundObject::GetBound(reference);

					return (Type)bound.DataId;
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static Type Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					int reference = (int)(intptr_t)lua_touserdata(lua, index);
					BoundObject& bound = BoundObject::GetBound(reference);

					return (Type)bound.DataId;
				}
			};
		};

		template <typename Type>
		struct BindType
		{
			static inline const int Returns = 1;

			static void Push(lua_State* lua, const Type& value)
			{
				int dataId = BoundTypeAllocators<Type>::AllocatedData.RequestID();

				BoundTypeAllocators<Type>::AllocatedData.GetNode(dataId).GetData() = value;

				std::pair<int, BoundObject*> bound = BoundObject::Allocate();

				bound.second->DataId = dataId;
				bound.second->ObjectType = LuaObjectType::Data;
				bound.second->Type = Meta::Reflected<Type>::GetMeta();
				bound.second->Destructor = [](BoundObject& bound)
				{
					BoundTypeAllocators<Type>::AllocatedData.Release(bound.DataId);
				};

				MakeBinding(lua, bound.first);
			}

			template <bool HasDefault>
			struct WithDefault
			{
				template <typename DefaultTraits>
				static Type& Pop(lua_State* lua, int index)
				{
					int reference = (int)(intptr_t)lua_touserdata(lua, index);
					BoundObject& bound = BoundObject::GetBound(reference);

					return BoundTypeAllocators<Type>::AllocatedData.GetNode(bound.DataId).GetData();
				}
			};

			template <>
			struct WithDefault<true>
			{
				template <typename DefaultTraits>
				static Type& Pop(lua_State* lua, int index)
				{
					if (index == -1)
						return DefaultTraits::Value;

					int reference = (int)(intptr_t)lua_touserdata(lua, index);
					BoundObject& bound = BoundObject::GetBound(reference);

					return BoundTypeAllocators<Type>::AllocatedData.GetNode(bound.DataId).GetData();
				}
			};
		};

		template <typename Type>
		std::shared_ptr<Type> GetObject(lua_State* lua)
		{
			return BindType<std::shared_ptr<Type>>::WithDefault<false>::Pop<void>(lua, 1);
		}
	}
}