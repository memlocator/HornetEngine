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
	namespace Editor
	{
		struct HierarchyItem
		{
			int HierarchyDepth = 0;
			Enum::HierarchyItemType ItemType = Enum::HierarchyItemType::None;
			std::shared_ptr<Object> FocusedItem;
			std::shared_ptr<Object> ParentItem;
		};

		class ExplorerDisplaySettings : public Object
		{
		public:
			void Initialize() {}
			void Update(float) {}

			void UpdateHierarchy();
			HierarchyItem GetObjectInHierarchy(float scrollPercent, int index);

		private:
			struct InternalHierarchyItem
			{
				int HierarchyDepth = 0;
				Enum::HierarchyItemType ItemType = Enum::HierarchyItemType::None;
				Object* FocusedItem;
				Object* ParentItem;
			};
			
			std::vector< InternalHierarchyItem> thing;

			Instantiable;

			Inherits_Class(Object);

			Reflected(ExplorerDisplaySettings);
		};
	}
}