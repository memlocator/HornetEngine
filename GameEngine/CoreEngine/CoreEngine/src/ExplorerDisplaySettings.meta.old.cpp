#include "ExplorerDisplaySettings.h"

namespace Engine
{
    Enum_Definition(HierarchyItemType,
        Document_Enum("");
        
        Enum_Item(GameObject);
        Enum_Item(HiddenChildren);
        Enum_Item(InternalChildren);
        Enum_Item(None);
    );


	Reflect_Type(HierarchyItem,
		Document_Class("");

		Document("");
		Archivable Class_Member(int, HierarchyDepth);

		Document("");
		Archivable Class_Member(LuaEnum<Enum::HierarchyItemType>, ItemType);

		Document("");
		Archivable Class_Member(std::shared_ptr<Object>, FocusedItem);

		Document("");
		Archivable Class_Member(std::shared_ptr<Object>, ParentItem);
	);

	namespace Editor
	{
		Reflect_Inherited(ExplorerDisplaySettings, Object,
			Document_Class("");

			Bind_Function(UpdateHierarchy,
		
				Document("");
				Function_Overload
				(
					Returns_Nothing;
					
					Overload_Parameters();
		
					Bind_Parameters_No_Return(UpdateHierarchy);
				);
			);

			Bind_Function(GetObjectInHierarchy,
		
				Document("");
				Function_Overload
				(
					Document("");
					Overload_Returns(HierarchyItem);
					
					Overload_Parameters
					(
						Document("");
						Function_Parameter(int, displayedObjects);

						Document("");
						Function_Parameter(float, scrollPercent);

						Document("");
						Function_Parameter(int, index);
					);
		
					Bind_Parameters(GetObjectInHierarchy, displayedObjects, scrollPercent, index);
				);
			);

			Bind_Function(GetHierarchyItems,
		
				Document("");
				Function_Overload
				(
					Document("");
					Overload_Returns(int);
					
					Overload_Parameters();
		
					Bind_Parameters(GetHierarchyItems);
				);
			);
		);
	}
}