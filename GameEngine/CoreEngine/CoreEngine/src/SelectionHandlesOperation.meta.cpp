#include "SelectionHandlesOperation.h"

#include "Selection.h"
#include "Scene.h"
#include "Camera.h"
#include "LuaInput.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace Editor;

		template <>
		void ReflectType<Enum::SelectionHandleType>()
		{
			Reflect<Enum::SelectionHandleType>::Enum
			(
				"SelectionHandleType",
				Value<Enum::SelectionHandleType::Move>("Move"),
				Value<Enum::SelectionHandleType::Resize>("Resize"),
				Value<Enum::SelectionHandleType::Rotate>("Rotate")
			);
		}

		template <>
		void ReflectType<SelectionHandlesOperation>()
		{
			Reflect<SelectionHandlesOperation, GraphicsEngine::RenderOperation>::Class
			(
				"SelectionHandlesOperation",
				{ "GameObject" },

				Member<Bind(&SelectionHandlesOperation::IsActive)>("IsActive"),
				Member<Bind(&SelectionHandlesOperation::DrawSelectionBox)>("DrawSelectionBox"),
				Member<Bind(&SelectionHandlesOperation::DrawHandles)>("DrawHandles"),
				Member<Bind(&SelectionHandlesOperation::Resolution)>("Resolution"),
				Member<Bind(&SelectionHandlesOperation::SelectionRayDistance)>("SelectionRayDistance"),

				Member<Bind(&SelectionHandlesOperation::SnapsToGrid)>("SnapsToGrid"),
				Member<Bind(&SelectionHandlesOperation::MinimumObjectSize)>("MinimumObjectSize"),
				Member<Bind(&SelectionHandlesOperation::GridLength)>("GridLength"),
				Member<Bind(&SelectionHandlesOperation::SnappingAngle)>("SnappingAngle"),

				Member<Bind(&SelectionHandlesOperation::IsLocalSpace)>("IsLocalSpace"),
				Member<Bind(&SelectionHandlesOperation::ObjectsShareHandles)>("ObjectsShareHandles"),
				Member<Bind(&SelectionHandlesOperation::HandleType)>("HandleType"),

				Member<Bind(&SelectionHandlesOperation::BoxColor)>("BoxColor"),
				Member<Bind(&SelectionHandlesOperation::HoverBoxColor)>("HoverBoxColor"),
				Member<Bind(&SelectionHandlesOperation::HandleColorX)>("HandleColorX"),
				Member<Bind(&SelectionHandlesOperation::HandleColorY)>("HandleColorY"),
				Member<Bind(&SelectionHandlesOperation::HandleColorZ)>("HandleColorZ"),

				Member<Bind(&SelectionHandlesOperation::HoverHandleColorX)>("HoverHandleColorX"),
				Member<Bind(&SelectionHandlesOperation::HoverHandleColorY)>("HoverHandleColorY"),
				Member<Bind(&SelectionHandlesOperation::HoverHandleColorZ)>("HoverHandleColorZ"),

				Member<Bind(&SelectionHandlesOperation::ArrowHandleMinSize)>("ArrowHandleMinSize"),
				Member<Bind(&SelectionHandlesOperation::ArrowHandleScaling)>("ArrowHandleScaling"),
				Member<Bind(&SelectionHandlesOperation::ArrowHandleMinOffset)>("ArrowHandleMinOffset"),
				Member<Bind(&SelectionHandlesOperation::ArrowHandleScaledOffset)>("ArrowHandleScaledOffset"),

				Member<Bind(&SelectionHandlesOperation::SphereHandleMinSize)>("SphereHandleMinSize"),
				Member<Bind(&SelectionHandlesOperation::SphereHandleScaling)>("SphereHandleScaling"),
				Member<Bind(&SelectionHandlesOperation::SphereHandleMinOffset)>("SphereHandleMinOffset"),
				Member<Bind(&SelectionHandlesOperation::SphereHandleScaledOffset)>("SphereHandleScaledOffset"),

				Member<Bind(&SelectionHandlesOperation::ActiveSelection)>("ActiveSelection"),
				Member<Bind(&SelectionHandlesOperation::TargetScene)>("TargetScene"),
				Member<Bind(&SelectionHandlesOperation::CurrentCamera)>("CurrentCamera"),

				Member<Bind(&SelectionHandlesOperation::MousePosition)>("MousePosition"),
				Member<Bind(&SelectionHandlesOperation::SelectButton)>("SelectButton"),
				Member<Bind(&SelectionHandlesOperation::DragButton)>("DragButton"),
				Member<Bind(&SelectionHandlesOperation::ResetButton)>("ResetButton"),
				Member<Bind(&SelectionHandlesOperation::RequiredModifierKey)>("RequiredModifierKey"),
				Member<Bind(&SelectionHandlesOperation::RequiredDragModifierKey)>("RequiredDragModifierKey"),
				Member<Bind(&SelectionHandlesOperation::MultiSelectModifierKey)>("MultiSelectModifierKey"),

				Member<Bind(&SelectionHandlesOperation::MoveToolKey)>("MoveToolKey"),
				Member<Bind(&SelectionHandlesOperation::ResizeToolKey)>("ResizeToolKey"),
				Member<Bind(&SelectionHandlesOperation::RotateToolKey)>("RotateToolKey"),
				Member<Bind(&SelectionHandlesOperation::ToggleEnabledKey)>("ToggleEnabledKey"),
				Member<Bind(&SelectionHandlesOperation::SelectToolKey)>("SelectToolKey"),

				Member<Bind(&SelectionHandlesOperation::ToggleLocalSpaceKey)>("ToggleLocalSpaceKey"),
				Member<Bind(&SelectionHandlesOperation::ToggleGroupSelectKey)>("ToggleGroupSelectKey")
			);
		}
	}
}