#include "Camera.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Camera>()
		{
			Reflect<Camera, Object>::Class
			(
				"Camera",
				{ "GameObject" },

				Member<Bind(&Camera::LightDirection)>("LightDirection"),

				Constructor(
					Overload()
				),

				Function(
					"SetTransformation",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Matrix3&>("newTransformation")
					).Bind<Camera, &Camera::SetTransformation>()
				),

				Function(
					"SetProperties",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<float>("fieldOfView"),
						Argument<float>("aspectRatio"),
						Argument<float>("near"),
						Argument<float>("far")
					).Bind<Camera, &Camera::SetProperties>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<float>("width"),
						Argument<float>("height"),
						Argument<float>("projectionPlane"),
						Argument<float>("near"),
						Argument<float>("far")
					).Bind<Camera, &Camera::SetProperties>()
				),

				Function(
					"GetTransformation",
					Overload(
						Const,
						Returns<const Matrix3&>()
					).Bind<Camera, &Camera::GetTransformation>()
				),

				Function(
					"GetTransformationInverse",
					Overload(
						Const,
						Returns<const Matrix3&>()
					).Bind<Camera, &Camera::GetTransformationInverse>()
				),

				Function(
					"GetProjectionMatrix",
					Overload(
						Const,
						Returns<const Matrix3&>()
					).Bind<Camera, &Camera::GetProjectionMatrix>()
				),

				Function(
					"GetProjection",
					Overload(
						Const,
						Returns<const Matrix3&>()
					).Bind<Camera, &Camera::GetProjection>()
				),

				Function(
					"GetDimensions",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Camera, &Camera::GetDimensions>()
				),

				Function(
					"GetProjectionPlane",
					Overload(
						Const,
						Returns<float>()
					).Bind<Camera, &Camera::GetProjectionPlane>()
				),

				Function(
					"GetNearPlane",
					Overload(
						Const,
						Returns<float>()
					).Bind<Camera, &Camera::GetNearPlane>()
				),

				Function(
					"GetFarPlane",
					Overload(
						Const,
						Returns<float>()
					).Bind<Camera, &Camera::GetFarPlane>()
				),

				Function(
					"GetAspectRatio",
					Overload(
						Const,
						Returns<float>()
					).Bind<Camera, &Camera::GetAspectRatio>()
				),

				Function(
					"GetFieldOfView",
					Overload(
						Const,
						Returns<float>()
					).Bind<Camera, &Camera::GetFieldOfView>()
				),

				Function(
					"GetRay",
					Overload(
						Const,
						Returns<Ray>(),
						Argument<int>("x"),
						Argument<int>("y"),
						Argument<int>("width"),
						Argument<int>("height"),
						Argument<float, Default(1.0f)>("length")
					).Bind<Camera, &Camera::GetRay>()
				),

				Function(
					"Moved",
					Overload(
						Const,
						Returns<bool>()
					).Bind<Camera, &Camera::Moved>()
				)
			);
		}
	}
}