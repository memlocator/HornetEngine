#pragma once

#include "Object.h"

struct HierarchyItemTypeEnum
{
	enum HierarchyItemType
	{
		GameObject,
		HiddenChildren,
		InternalChildren,

		None
	};
};

namespace Enum
{
	typedef HierarchyItemTypeEnum::HierarchyItemType HierarchyItemType;
}

namespace Engine
{
	struct HierarchyItem
	{
		int HierarchyDepth = 0;
		Enum::HierarchyItemType ItemType = Enum::HierarchyItemType::None;
		std::shared_ptr<Object> FocusedItem;
		std::shared_ptr<Object> ParentItem;
	};

	namespace Editor
	{
		class ExplorerDisplaySettings : public Object
		{
		public:
			int MaxDepth = -1;

			void UpdateHierarchy();
			HierarchyItem GetObjectInHierarchy(int displayedObjects, float scrollPercent, int index);
			int GetHierarchyItems() const;
			bool CanShow(Object* object) const;
			bool ChildrenCanShow(Object* object) const;
			bool HasHiddenChildren(Object* object) const;
			bool HasInternalChildren(Object* object) const;

		private:
			struct InternalHierarchyItem
			{
				int HierarchyDepth = 0;
				Enum::HierarchyItemType ItemType = Enum::HierarchyItemType::None;
				Object* FocusedItem;
				Object* ParentItem;
			};
			
			std::vector<InternalHierarchyItem> HierarchyItems;

			void Traverse(Object* object, Object* parent = nullptr, int depth = 0);
		};
	}
}