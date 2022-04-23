#include "ScrollBar.h"

#include "DeviceTransform.h"
#include "ScreenCanvas.h"

namespace Engine
{
    Enum_Definition(ScrollBarOrientation,
        Document_Enum("");
        
        Enum_Item(Vertical);
        Enum_Item(Horizontal);
    );
}

namespace GraphicsEngine
{
	using Engine::Object;

	Reflect_Inherited(ScrollBar, Object,
		Document_Class("");

		Bind_Function(GetFrameTransform,

			Document("");
			Function_Overload
			(
				Document("");
				Overload_Returns(std::shared_ptr<DeviceTransform>);

				Overload_Parameters();

				Bind_Parameters(GetFrameTransform);
			);
		);

		Bind_Function(GetFrameCanvas,

			Document("");
			Function_Overload
			(
				Document("");
				Overload_Returns(std::shared_ptr<ScreenCanvas>);

				Overload_Parameters();

				Bind_Parameters(GetFrameCanvas);
			);
		);
		Bind_Function(GetBarTransform,

			Document("");
			Function_Overload
			(
				Document("");
				Overload_Returns(std::shared_ptr<DeviceTransform>);

				Overload_Parameters();

				Bind_Parameters(GetBarTransform);
			);
		);

		Bind_Function(GetBarCanvas,

			Document("");
			Function_Overload
			(
				Document("");
				Overload_Returns(std::shared_ptr<ScreenCanvas>);

				Overload_Parameters();

				Bind_Parameters(GetBarCanvas);
			);
		);

		Bind_Function(SetBarSize,

			Document("");
			Function_Overload
			(
				Document("");
				Returns_Nothing;

				Overload_Parameters
				(
					Document("");
					Function_Parameter(float, percent);
				);

				Bind_Parameters_No_Return(SetBarSize, percent);
			);
		);

		Bind_Function(SetBarPercent,

			Document("");
			Function_Overload
			(
				Document("");
				Returns_Nothing;

				Overload_Parameters
				(
					Document("");
					Function_Parameter(float, percent);
				);

				Bind_Parameters_No_Return(SetBarPercent, percent);
			);
		);

		Bind_Function(SetBarOrientation,

			Document("");
			Function_Overload
			(
				Document("");
				Returns_Nothing;

				Overload_Parameters
				(
					Document("");
					Function_Parameter(LuaEnum<Enum::ScrollBarOrientation>, orientation);
				);

				Bind_Parameters_No_Return(SetBarOrientation, orientation);
			);
		);

		Bind_Function(GetBarSize,

			Document("");
			Function_Overload
			(
				Document("");
				Overload_Returns(float);

				Overload_Parameters();

				Bind_Parameters(GetBarSize);
			);
		);

		Bind_Function(GetBarPercent,

			Document("");
			Function_Overload
			(
				Document("");
				Overload_Returns(float);

				Overload_Parameters();

				Bind_Parameters(GetBarPercent);
			);
		);

		Bind_Function(GetBarOrientation,

			Document("");
			Function_Overload
			(
				Document("");
				Overload_Returns(LuaEnum<Enum::ScrollBarOrientation>);

				Overload_Parameters();

				Bind_Parameters(GetBarOrientation);
			);
		);

		Document("");
		Register_Lua_Property(FrameTransform,
			Property_Getter(GetFrameTransform, std::shared_ptr<DeviceTransform>);
			
			Property_Setters();
		);

		Document("");
		Register_Lua_Property(FrameCanvas,
			Property_Getter(GetFrameCanvas, std::shared_ptr<ScreenCanvas>);
			
			Property_Setters();
		);

		Document("");
		Register_Lua_Property(BarTransform,
			Property_Getter(GetBarTransform, std::shared_ptr<DeviceTransform>);
			
			Property_Setters();
		);

		Document("");
		Register_Lua_Property(BarCanvas,
			Property_Getter(GetBarCanvas, std::shared_ptr<ScreenCanvas>);
			
			Property_Setters();
		);

		Document("");
		Register_Lua_Property(BarSize,
			Property_Getter(GetBarSize, float);
			
			Property_Setters(
				Bind_Setter(SetBarSize, float);
			);
		);

		Document("");
		Register_Lua_Property(BarPercent,
			Property_Getter(GetBarPercent, float);
			
			Property_Setters(
				Bind_Setter(SetBarPercent, float);
			);
		);

		Document("");
		Register_Lua_Property(BarOrientation,
			Property_Getter(GetBarOrientation, LuaEnum<Enum::ScrollBarOrientation>);
			
			Property_Setters(
				Bind_Setter(SetBarOrientation, LuaEnum<Enum::ScrollBarOrientation>);
			);
		);
	);
}