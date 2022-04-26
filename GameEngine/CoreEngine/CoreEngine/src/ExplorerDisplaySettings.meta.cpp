#include "ExplorerDisplaySettings.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace Editor;

		template <>
		void ReflectType<Enum::HierarchyItemType>()
		{
			Reflect<Enum::HierarchyItemType>::Enum
			(
				"HierarchyItemType",
				Value<Enum::HierarchyItemType::GameObject>("Value0"),
				Value<Enum::HierarchyItemType::HiddenChildren>("Value1"),
				Value<Enum::HierarchyItemType::InternalChildren>("Value2"),

				Value<Enum::HierarchyItemType::None>("AllValues")
			);
		}

		template <>
		void ReflectType<HierarchyItem>()
		{
			Reflect<HierarchyItem>::Type
			(
				"HierarchyItem",

				Member<Bind(&HierarchyItem::HierarchyDepth)>("HierarchyDepth"),
				Member<Bind(&HierarchyItem::ItemType)>("ItemType"),
				Member<Bind(&HierarchyItem::FocusedItem)>("FocusedItem"),
				Member<Bind(&HierarchyItem::ParentItem)>("ParentItem"),

				Constructor(
					Overload()
				)
			);
		}

		template <>
		void ReflectType<ExplorerDisplaySettings>()
		{
			Reflect<ExplorerDisplaySettings, Object>::Class
			(
				"ExplorerDisplaySettings",
				{ "GameObject" },

				Member<Bind(&ExplorerDisplaySettings::MaxDepth)>("MaxDepth"),

				Constructor(
					Overload()
				),

				Function(
					"UpdateHierarchy",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<ExplorerDisplaySettings, &ExplorerDisplaySettings::UpdateHierarchy>()
				),

				Function(
					"GetObjectInHierarchy",
					Overload(
						Mutable,
						Returns<HierarchyItem>(),
						Argument<int>("displayedObjects"),
						Argument<float>("scrollPercent"),
						Argument<int>("index")
					).Bind<ExplorerDisplaySettings, &ExplorerDisplaySettings::GetObjectInHierarchy>()
				),

				Function(
					"GetHierarchyItems",
					Overload(
						Const,
						Returns<int>()
					).Bind<ExplorerDisplaySettings, &ExplorerDisplaySettings::GetHierarchyItems>()
				)
			);
		}
	}
}