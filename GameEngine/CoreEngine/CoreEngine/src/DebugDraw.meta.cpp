#include "DebugDraw.h"

#include "ModelAsset.h"
#include "Material.h"
#include "Scene.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<DebugDraw>()
		{
			Reflect<DebugDraw, Object>::Class
			(
				"DebugDraw",
				{ "GameObject" },

				Member<Bind(&DebugDraw::LineAsset)>("LineAsset"),
				Member<Bind(&DebugDraw::TriangleAsset)>("TriangleAsset"),
				Member<Bind(&DebugDraw::MaterialProperties)>("MaterialProperties"),

				Constructor(
					Overload()
				),

				Function(
					"GetScene",
					Overload(
						Mutable,
						Returns<std::shared_ptr<GraphicsEngine::Scene>>()
					).Bind<DebugDraw, &DebugDraw::GetScene>()
				),

				Function(
					"Reset",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<DebugDraw, &DebugDraw::Reset>()
				),

				Function(
					"Clear",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<DebugDraw, &DebugDraw::Clear>()
				),

				Function(
					"DrawLine",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("point1"),
						Argument<const Vector3&>("point2"),
						Argument<const RGBA&, Default(RGBA(0xFFFFFFFF))>("color"),
						Argument<float, Default(0.1f)>("thickness"),
						Argument<bool, Default(false)>("glows")
					).Bind<DebugDraw, &DebugDraw::DrawLine>()
				),

				Function(
					"DrawTriangle",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("point1"),
						Argument<const Vector3&>("point2"),
						Argument<const Vector3&>("point3"),
						Argument<const RGBA&, Default(RGBA(0xFFFFFFFF))>("color"),
						Argument<float, Default(0.1f)>("thickness"),
						Argument<bool, Default(false)>("glows")
					).Bind<DebugDraw, &DebugDraw::DrawTriangle>()
				)
			);
		}
	}
}