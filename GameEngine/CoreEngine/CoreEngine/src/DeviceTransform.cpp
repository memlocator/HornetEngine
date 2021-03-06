#include "DeviceTransform.h"

#include "ScreenCanvas.h"
#include "CanvasStencil.h"
#include "Text.h"
#include "FrameBuffer.h"

namespace GraphicsEngine
{
	DeviceTransform::~DeviceTransform()
	{

	}

	void DeviceTransform::Initialize()
	{
		Engine::Object::Initialize();

		SetTicks(true);
	}

	void DeviceTransform::Update(Float delta)
	{
		Engine::Object::Update(delta);

		UpdateTransformation();
	}

	void DeviceTransform::Draw(bool updateStencils)
	{
		Draw(This.lock(), updateStencils);
	}

	Matrix4 DeviceTransform::GetTransformation() const
	{
		return Transformation;
	}

	Matrix4 DeviceTransform::GetTransformation()
	{
		UpdateTransformation();

		return Transformation;
	}

	Matrix4 DeviceTransform::GetInverseTransformation() const
	{
		return InverseTransformation;
	}

	Matrix4 DeviceTransform::GetInverseTransformation()
	{
		UpdateTransformation();

		return InverseTransformation;
	}

	Vector3 DeviceTransform::GetAbsoluteSize() const
	{
		return AbsoluteSize;
	}

	Vector3 DeviceTransform::GetAbsoluteSize()
	{
		UpdateTransformation();

		return ((const DeviceTransform*)this)->GetAbsoluteSize();
	}

	Vector3 DeviceTransform::GetAbsolutePosition(const DeviceVector& point) const
	{
		return Transformation * GetLocalPosition(point);
	}

	Vector3 DeviceTransform::GetAbsolutePosition(const DeviceVector& point)
	{
		UpdateTransformation();

		return ((const DeviceTransform*)this)->GetAbsolutePosition(point);
	}

	Vector3 DeviceTransform::GetLocalPosition(const DeviceVector& point) const
	{
		return Vector3(
			point.X.Scale * AbsoluteSize.X + point.X.Offset,
			point.Y.Scale * AbsoluteSize.Y + point.Y.Offset,
			0._F,
			1._F
		);
	}

	Vector3 DeviceTransform::GetLocalPosition(const DeviceVector& point)
	{
		UpdateTransformation();

		return ((const DeviceTransform*)this)->GetLocalPosition(point);
	}

	Vector3 DeviceTransform::GetLocalPosition(const Vector3& point) const
	{
		return InverseTransformation * point;
	}

	Vector3 DeviceTransform::GetLocalPosition(const Vector3& point)
	{
		UpdateTransformation();

		return ((const DeviceTransform*)this)->GetLocalPosition(point);
	}

	Vector3 DeviceTransform::GetResolution() const
	{
		std::shared_ptr<DeviceTransform> parent = GetComponent<DeviceTransform>();

		if (parent != nullptr)
			return parent->GetResolution();

		return AbsoluteSize;
	}

	bool DeviceTransform::ContainsLocalPoint(const Vector3& point) const
	{
		return (point.X >= 0 && point.X < AbsoluteSize.X) && (point.Y >= 0 && point.Y < AbsoluteSize.Y);
	}

	bool DeviceTransform::ContainsLocalPoint(const Vector3& point)
	{
		UpdateTransformation();

		return ((const DeviceTransform*)this)->ContainsLocalPoint(point);
	}

	bool DeviceTransform::ContainsPoint(const Vector3& point) const
	{
		return ContainsLocalPoint(GetLocalPosition(point));
	}

	bool DeviceTransform::ContainsPoint(const Vector3& point)
	{
		UpdateTransformation();

		return ((const DeviceTransform*)this)->ContainsPoint(point);
	}

	Dimensions GetBufferResolution()
	{
		std::shared_ptr<FrameBuffer> attached = FrameBuffer::GetAttachedBuffer();

		if (attached != nullptr)
			return attached->GetSize();

		return FrameBuffer::WindowSize;
	}

	bool DeviceTransform::HasMoved() const
	{
		if (Size != LastSize || Position != LastPosition || Rotation != LastRotation || AnchorPoint != LastAnchorPoint || RotationAnchor != LastRotationAnchor)
			return true;

		std::shared_ptr<DeviceTransform> parent = GetComponent<DeviceTransform>();

		if (parent != nullptr && parent->HasMoved())
			return true;

		return false;
	}

	bool DeviceTransform::IsVisible() const
	{
		if (!Visible)
			return false;

		std::shared_ptr<DeviceTransform> parent = GetComponent<DeviceTransform>();

		if (parent != nullptr)
			return parent->IsVisible();

		return Visible;
	}

	bool DeviceTransform::IsEnabled() const
	{
		if (!Enabled)
			return false;

		std::shared_ptr<DeviceTransform> parent = GetComponent<DeviceTransform>();

		if (parent != nullptr)
			return parent->IsEnabled();

		return Enabled;
	}

	void DeviceTransform::UpdateTransformation()
	{
		if (!HasMoved())
			return;

		Vector3 parentSize;
		Matrix4 parentTransformation;

		std::shared_ptr<DeviceTransform> parent = InheritTransformation ? GetComponent<DeviceTransform>() : nullptr;

		if (parent != nullptr)
		{
			parent->UpdateTransformation();

			parentSize = parent->GetAbsoluteSize();
			parentTransformation = parent->GetTransformation();
		}
		else
		{
			Dimensions size = GetBufferResolution();

			parentSize.Set(float(size.Width), float(size.Height));
		}

		AbsoluteSize = Vector3(
			parentSize.X * Size.X.Scale + Size.X.Offset,
			parentSize.Y * Size.Y.Scale + Size.Y.Offset
		);

		Vector3 rotationOffset = 2._F * RotationAnchor.Calculate(Vector3(), AbsoluteSize).Scale(1, 1, 1);

		Vector3 scale = AbsoluteSize + Vector3(0, 0, 1);
		Vector3 translation = Vector3(
			2 * (Position.X.Offset + parentSize.X * Position.X.Scale - AnchorPoint.X.Offset - AbsoluteSize.X * AnchorPoint.X.Scale),
			2 * (Position.Y.Offset + parentSize.Y * Position.Y.Scale - AnchorPoint.Y.Offset - AbsoluteSize.Y * AnchorPoint.Y.Scale)
		) - (parentSize - AbsoluteSize);

		translation = translation.Scale(1, -1, 1);

		Vector3 scaling(1, 1, 1);

		if (parentSize.X != 0)
			scaling.X = 1 / parentSize.X;
		
		if (parentSize.Y != 0)
			scaling.Y = 1 / parentSize.Y;

		Transformation = Matrix4(true).Scale(scaling) * Matrix4(translation + rotationOffset) * Matrix4(true).RotateRoll(Rotation) * Matrix4(-rotationOffset) * Matrix4(true).Scale(scale);

		if (parent != nullptr)
			Transformation = parent->GetTransformation() * Transformation;

		Transformation = Transformation;

		InverseTransformation.Invert(Transformation);

		LastSize = Size;
		LastPosition = Position;

		TransformChanged.Fire();
	}

	void DeviceTransform::Draw(std::shared_ptr<Object> object, bool updateStencils)
	{
		for (int i = 0; i < object->GetChildren(); ++i)
		{
			std::shared_ptr<Object> child = object->Get(i);

			if (child->IsA<DeviceTransform>())
			{
				if (child->Cast<DeviceTransform>()->Visible && child->GetComponent<DeviceTransform>() == This.lock())
				{
					child->Cast<DeviceTransform>()->Draw();

					Draw(child, updateStencils);
				}
			}
			else if (child->IsA<ScreenCanvas>())
			{
				if (child->Cast<ScreenCanvas>()->Visible)
				{
					if (!updateStencils && child->GetComponent<DeviceTransform>() == This.lock())
						child->Cast<ScreenCanvas>()->Draw();
				}
				Draw(child, updateStencils);
			}
			else if (child->IsA<Text>())
			{
				if (!updateStencils && child->GetComponent<DeviceTransform>() == This.lock())
					child->Cast<Text>()->Draw(FrameBuffer::GetAttachedBuffer());
				
				Draw(child, updateStencils);
			}
			else if (child->IsA<CanvasStencil>())
			{
				if (updateStencils && child->Cast<CanvasStencil>()->Enabled && child->GetComponent<DeviceTransform>() == This.lock())
					child->Cast<CanvasStencil>()->Draw();

				Draw(child, updateStencils);
			}
			else
				Draw(child, updateStencils);
		}
	}
}