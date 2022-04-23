#include "BoundObject.h"

namespace Engine
{
	namespace Lua
	{
		BoundObject& BoundObject::GetBound(int id)
		{
			static BoundObject NullObject;

			if (id < 0 || id > BoundObjects.Size())
				return NullObject;

			return BoundObjects.GetNode(id).GetData();
		}

		void BoundObject::ReleaseBound(int id)
		{
			BoundObjects.Release(id);
		}

		std::pair<int, BoundObject*> BoundObject::Allocate()
		{
			int id = BoundObjects.RequestID();

			return std::make_pair(id, &GetBound(id));
		}
	}
}