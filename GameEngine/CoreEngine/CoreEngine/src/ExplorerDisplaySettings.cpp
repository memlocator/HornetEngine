#include "ExplorerDisplaySettings.h"

#include <cmath>

#include "Engine.h"
#include "GameEngine.h"

namespace Engine
{
	namespace Editor
	{
		int rangeRound(int max, float percent)
		{
			return std::min(int(std::floor(float(max + 1) * percent)), max);
		}

		HierarchyItem ExplorerDisplaySettings::GetObjectInHierarchy(int displayedObjects, float scrollPercent, int index)
		{
			int count = GetHierarchyItems();
			int scrollRange = std::max(count - displayedObjects, 0);
			int itemIndex = index;
			
			if (scrollRange != 0)
				itemIndex += rangeRound(scrollRange, scrollPercent);

			if (itemIndex > count)
				return HierarchyItem{ 0, Enum::HierarchyItemType::None, nullptr, nullptr };

			InternalHierarchyItem& item = HierarchyItems[itemIndex];

			return HierarchyItem{ item.HierarchyDepth, item.ItemType, item.FocusedItem->Cast<Object>(), item.ParentItem != nullptr ? item.ParentItem->Cast<Object>() : nullptr };
		}

		void ExplorerDisplaySettings::UpdateHierarchy()
		{
			HierarchyItems.clear();

			Traverse(Engine::Root().get());
		}

		int ExplorerDisplaySettings::GetHierarchyItems() const
		{
			return int(HierarchyItems.size());
		}

		bool ExplorerDisplaySettings::CanShow(Object* object) const
		{
			return true;
		}

		bool ExplorerDisplaySettings::ChildrenCanShow(Object* object) const
		{
			return true;
		}

		bool ExplorerDisplaySettings::HasHiddenChildren(Object* object) const
		{
			return false;
		}

		bool ExplorerDisplaySettings::HasInternalChildren(Object* object) const
		{
			return false;
		}

		void ExplorerDisplaySettings::Traverse(Object* object, Object* parent, int depth)
		{
			if (!CanShow(object) || (MaxDepth != -1 && depth > MaxDepth))
				return;

			HierarchyItems.push_back(InternalHierarchyItem{ depth, Enum::HierarchyItemType::GameObject, object, parent });

			if (object->HasChildren())
			{
				if (ChildrenCanShow(object))
					for (int i = 0; i < object->GetChildren(); ++i)
						Traverse(object->Get(i).get(), object, depth + 1);

				if (HasHiddenChildren(object) || (MaxDepth != -1 && depth + 1 > MaxDepth))
					HierarchyItems.push_back(InternalHierarchyItem{ depth + 1, Enum::HierarchyItemType::HiddenChildren, nullptr, object });

				if (HasInternalChildren(object))
					HierarchyItems.push_back(InternalHierarchyItem{ depth + 1, Enum::HierarchyItemType::InternalChildren, nullptr, object });
			}
		}
	}
}