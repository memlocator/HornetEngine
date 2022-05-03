#pragma once

#include "RenderOperation.h"
#include "Object.h"
#include "Math/Color4.h"
#include "Aabb.h"
#include "Math/Matrix4.h"
#include "InputEnums.h"
#include "Constants.h"

namespace GraphicsEngine
{
	class Camera;
	class Scene;
	class SceneObject;
}

struct SelectionHandleTypeEnum
{
	enum SelectionHandleType
	{
		Move,
		Resize,
		Rotate
	};
};

namespace Enum
{
	typedef SelectionHandleTypeEnum::SelectionHandleType SelectionHandleType;
}

class Mesh;
class MeshData;
class Ray;

namespace Engine
{
	class InputObject;
	class Transform;

	namespace Editor
	{

		struct SelectedAxisEnum
		{
			enum SelectedAxis
			{
				None,

				AxisX,
				AxisY,
				AxisZ,

				AxisNegativeX,
				AxisNegativeY,
				AxisNegativeZ
			};
		};

		class Selection;
		
		class SelectionHandlesOperation : public GraphicsEngine::RenderOperation
		{
		public:
			bool IsActive = true;
			bool DrawSelectionBox = true;
			bool DrawHandles = true;
			Vector3 Resolution;
			Float SelectionRayDistance = 10000;

			bool SnapsToGrid = true;
			Float MinimumObjectSize = 0.01f;
			Float GridLength = 0.5f;
			Float SnappingAngle = PI / 16.f;

			bool IsLocalSpace = false;
			bool ObjectsShareHandles = true;
			Enum::SelectionHandleType HandleType = Enum::SelectionHandleType::Move;

			Color4 BoxColor = Color4(0, 0.75f, 1);
			Color4 HoverBoxColor = Color4(0.85f, 0.95f, 1);
			Color4 HandleColorX = Color4(1, 0.2f, 0.2f);
			Color4 HandleColorY = Color4(0.2f, 1, 0.2f);
			Color4 HandleColorZ = Color4(0.2f, 0.2f, 1);

			Color4 HoverHandleColorX = Color4(1, 0.75f, 0.75f);
			Color4 HoverHandleColorY = Color4(0.75f, 1, 0.75f);
			Color4 HoverHandleColorZ = Color4(0.75f, 0.75f, 1);

			Float ArrowHandleMinSize = 0.15f;
			Float ArrowHandleScaling = 0.15f;
			Float ArrowHandleMinOffset = 0.1f;
			Float ArrowHandleScaledOffset = 0.1f;

			Float SphereHandleMinSize = 0.1f;
			Float SphereHandleScaling = 0.1f;
			Float SphereHandleMinOffset = 0.2f;
			Float SphereHandleScaledOffset = 0.2f;

			std::weak_ptr<Selection> ActiveSelection;
			std::weak_ptr<GraphicsEngine::Scene> TargetScene;
			std::weak_ptr<GraphicsEngine::Camera> CurrentCamera;

			std::weak_ptr<InputObject> MousePosition = GetInput(Enum::InputCode::MousePosition);
			std::weak_ptr<InputObject> SelectButton = GetInput(Enum::InputCode::MouseLeft);
			std::weak_ptr<InputObject> DragButton = GetInput(Enum::InputCode::MouseLeft);
			std::weak_ptr<InputObject> ResetButton = GetInput(Enum::InputCode::MouseRight);
			std::weak_ptr<InputObject> RequiredModifierKey;
			std::weak_ptr<InputObject> RequiredDragModifierKey;
			std::weak_ptr<InputObject> MultiSelectModifierKey = GetInput(Enum::InputCode::LeftControl);

			std::weak_ptr<InputObject> MoveToolKey = GetInput(Enum::InputCode::T);
			std::weak_ptr<InputObject> ResizeToolKey = GetInput(Enum::InputCode::G);
			std::weak_ptr<InputObject> RotateToolKey = GetInput(Enum::InputCode::R);
			std::weak_ptr<InputObject> ToggleEnabledKey = GetInput(Enum::InputCode::End);
			std::weak_ptr<InputObject> SelectToolKey = GetInput(Enum::InputCode::F);

			std::weak_ptr<InputObject> ToggleLocalSpaceKey = GetInput(Enum::InputCode::L);
			std::weak_ptr<InputObject> ToggleGroupSelectKey = GetInput(Enum::InputCode::O);

			void Render();

		private:
			typedef SelectedAxisEnum::SelectedAxis SelectedAxis;

			struct ObjectHandleHit
			{
				bool HitHandle = false;
				Float ClosestDistance = std::numeric_limits<Float>::max();
				GraphicsEngine::SceneObject* Object = nullptr;
				SelectedAxis Axis = SelectedAxis::None;
				Matrix4 Transformation;
				const Mesh* RenderMesh = nullptr;
			};

			struct HandleMesh
			{
				const MeshData* Data = nullptr;
				const Mesh* RenderMesh = nullptr;
			};

			struct MovingObjectData
			{
				std::shared_ptr<GraphicsEngine::SceneObject> Object;
				std::shared_ptr<Transform> ObjectTransform;
				Matrix4 InitialTransformation;
				Matrix4 ParentInverseTransformation;
				Matrix4 ParentTransformation;
			};

			typedef std::vector<MovingObjectData> MovingObjectVector;

			int SelectedObjects = 0;
			Selection* ActiveSelectionRaw = nullptr;
			const HandleMesh RingMesh = GetCoreMesh("CoreRing");
			const HandleMesh ArrowMesh = GetCoreMesh("CoreArrow");
			const HandleMesh SphereMesh = GetCoreMesh("CoreSphere");

			bool IsMovingObject = false;
			bool MovingInLocalSpace = false;
			SelectedAxis CurrentMovementHandle = SelectedAxis::None;
			Vector3 InitialCursorPoint;
			Vector3 HandlePosition;
			Vector3 HandleAxis;
			Aabb MovingBox;
			MovingObjectVector MovingObjects;

			Color4 GetColor(SelectedAxis axis) const;
			Color4 GetHoverColor(SelectedAxis axis) const;
			Vector3 GetMouseHandlePoint(const std::shared_ptr<GraphicsEngine::Camera>& camera, const Ray& mouseRay) const;
			Float GetMouseHandleValue(const std::shared_ptr<GraphicsEngine::Camera>& camera, const Vector3& mousePoint) const;
			void UpdateObject(int index, Float handleValue);
			HandleMesh GetCoreMesh(const std::string& name) const;
			void ProcessInput();
			Aabb DrawSelection(ObjectHandleHit& closestHit, const Ray& ray, const std::shared_ptr<GraphicsEngine::Camera>& camera, const std::shared_ptr<GraphicsEngine::SceneObject>& object, bool isHovered);
			bool DrawSelection(ObjectHandleHit& closestHit, const Ray& ray, const std::shared_ptr<GraphicsEngine::Camera>& camera, const Aabb& box, const Matrix4& transformation, const Matrix4& transformationInverse, bool drawHandles, bool isHovered);
			bool DrawAxisHandle(const HandleMesh& mesh, const Ray& ray, const Matrix4& transformation, const Matrix4& inverseTransformation, ObjectHandleHit& closestHit, SelectedAxis axis);
			void ProcessObjectInput(const std::shared_ptr<GraphicsEngine::SceneObject>& object, const Vector3& intersection);
			void ProcessObjectInput(const std::shared_ptr<GraphicsEngine::SceneObject>& object, const Vector3& intersection, SelectedAxis axis);

			static std::shared_ptr<InputObject> GetInput(Enum::InputCode code);
		};
	}
}