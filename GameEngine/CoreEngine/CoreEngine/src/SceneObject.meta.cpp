#include "Scene.h"

#include "PhysicalMaterial.h"
#include "Camera.h"
#include "Material.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<SceneObject>()
		{
			Reflect<SceneObject, Object>::Class
			(
				"SceneObject",
				{ "GameObject" },

				Member<Bind(&SceneObject::Visible)>("Visible"),
				Member<Bind(&SceneObject::PhysicalMaterialProperties)>("PhysicalMaterialProperties"),

				Constructor(
					Overload()
				),

				Property(
					"MaterialProperties",
					Getter<std::shared_ptr<Material>>(Const).Bind<SceneObject, &SceneObject::GetMaterial>(),
					Setter<const std::shared_ptr<Material>&>(Mutable).Bind<SceneObject, &SceneObject::SetMaterial>()
				),

				Function(
					"GetBoundingBox",
					Overload(
						Const,
						Returns<Aabb>()
					).Bind<SceneObject, &SceneObject::GetBoundingBox>()
				),

				Function(
					"GetLocalBoundingBox",
					Overload(
						Const,
						Returns<Aabb>()
					).Bind<SceneObject, &SceneObject::GetLocalBoundingBox>()
				),

				Function(
					"GetTransformation",
					Overload(
						Const,
						Returns<Matrix3>()
					).Bind<SceneObject, &SceneObject::GetTransformation>()
				),

				Function(
					"GetInverseTransformation",
					Overload(
						Const,
						Returns<Matrix3>()
					).Bind<SceneObject, &SceneObject::GetInverseTransformation>()
				),

				Function(
					"HasMoved",
					Overload(
						Const,
						Returns<bool>()
					).Bind<SceneObject, &SceneObject::HasMoved>()
				),

				Function(
					"IsStatic",
					Overload(
						Const,
						Returns<bool>()
					).Bind<SceneObject, &SceneObject::IsStatic>()
				),

				Function(
					"Draw",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Camera>&>("camera")
					).Bind<SceneObject, &SceneObject::Draw>()
				),

				Function(
					"IsTransparent",
					Overload(
						Const,
						Returns<bool>()
					).Bind<SceneObject, &SceneObject::IsTransparent>()
				),

				Function(
					"UseDepthBuffer",
					Overload(
						Const,
						Returns<bool>()
					).Bind<SceneObject, &SceneObject::UseDepthBuffer>()
				),

				Function(
					"GetMeshId",
					Overload(
						Const,
						Returns<int>()
					).Bind<SceneObject, &SceneObject::GetMeshId>()
				),

				Function(
					"GetMeshId",
					Overload(
						Const,
						Returns<int>()
					).Bind<SceneObject, &SceneObject::GetMeshId>()
				),

				Function(
					"SetMaterial",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Material>&>("material")
					).Bind<SceneObject, &SceneObject::SetMaterial>()
				),

				Function(
					"GetMaterial",
					Overload(
						Const,
						Returns<std::shared_ptr<Material>>()
					).Bind<SceneObject, &SceneObject::GetMaterial>()
				)
			);
		}
	}
}