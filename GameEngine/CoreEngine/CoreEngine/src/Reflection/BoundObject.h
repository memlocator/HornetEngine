#pragma once

#include <memory>
#include "../IdentifierHeap.h"

namespace Engine
{
	class Object;

	namespace Meta
	{
		struct ReflectedType;
	}

	namespace Lua
	{
		struct LuaObjectTypeEnum
		{
			enum LuaObjectType
			{
				Object,
				Data,
				Enum,

				Unknown
			};
		};

		typedef LuaObjectTypeEnum::LuaObjectType LuaObjectType;

		class BoundObject
		{
		public:
			typedef void (*DestructorCallback)(BoundObject& bound);

			std::shared_ptr<Object> GameObject;
			const Meta::ReflectedType* Type = nullptr;
			int DataId = -1;
			LuaObjectType ObjectType = LuaObjectType::Unknown;
			DestructorCallback Destructor = nullptr;

			static inline IDHeap<BoundObject> BoundObjects;

			static BoundObject& GetBound(int id);
			static void ReleaseBound(int id);
			static std::pair<int, BoundObject*> Allocate();
		};
	}
}