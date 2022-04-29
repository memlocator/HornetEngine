#pragma once

#include "ShaderProgram.h"
#include "Matrix4.h"
#include "Object.h"
#include "Frustum.h"
#include "Ray.h"

namespace GraphicsEngine
{
	class Camera : public Engine::Object
	{
	public:
		virtual ~Camera() {}

		void Update(Float);

		Vector3 LightDirection;

		void SetTransformation(const Matrix4& newTransformation);
		void SetProperties(Float fieldOfView, Float aspectRatio, Float near, Float far);
		void SetProperties(Float width, Float height, Float projectionPlane, Float near, Float far);
		const Matrix4& GetTransformation() const;
		const Matrix4& GetTransformationInverse() const;
		const Matrix4& GetProjectionMatrix() const;
		const Matrix4& GetProjection() const;
		Vector3 GetDimensions() const;
		Float GetProjectionPlane() const;
		Float GetNearPlane() const;
		Float GetFarPlane() const;
		Float GetAspectRatio() const;
		Float GetFieldOfView() const;
		const Frustum& GetFrustum() const;
		Ray GetRay(int x, int y, int resolutionX, int resolutionY, Float length = 1) const;
		bool Moved() const;

	private:
		Matrix4 PerspectiveProjection;
		Matrix4 Transformation;
		Matrix4 InverseTransformation;
		Matrix4 Projection;
		Frustum CameraFrustum;
		bool HasMoved = false;

		Float Width = 0, Height = 0, ProjectionPlane = 0, NearPlane = 0, FarPlane = 0, AspectRatio = 0, FieldOfView = 0;

		void CalculateProjectionMatrix();
		void CalculateFrustum();
		void MarkMoved();
	};
}