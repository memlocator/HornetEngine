#include "EditorPackage.h"

#include "Selection.h"
#include "ExplorerDisplaySettings.h"
#include "SelectionHandlesOperation.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		extern void ReflectType<Editor::Selection>();
		
		template <>
		extern void ReflectType<Editor::ExplorerDisplaySettings>();
		
		template <>
		extern void ReflectType<Editor::SelectionHandlesOperation>();
		
		template <>
		extern void ReflectType<HierarchyItem>();
		
		template <>
		extern void ReflectType<Enum::HierarchyItemType>();
		
		template <>
		extern void ReflectType<Enum::SelectionHandleType>();

		template <>
		void ReflectPackage<EditorPackage>()
		{
			ReflectFromPackage<
				Editor::Selection,
				Editor::ExplorerDisplaySettings,
				Editor::SelectionHandlesOperation,
				HierarchyItem,
				Enum::HierarchyItemType,
				Enum::SelectionHandleType
			>();
		}
	}
}