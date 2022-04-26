#include "CanvasStencil.h"

#include "Texture.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<CanvasStencil>()
		{
			Reflect<CanvasStencil, Object>::Class
			(
				"CanvasStencil",
				{ "GameObject" },

				Member<Bind(&CanvasStencil::Enabled)>("Enabled"),

				Constructor(
					Overload()
				),

				Function(
					"GetTexture",
					Overload(
						Mutable,
						Returns<std::shared_ptr<Texture>>()
					).Bind<CanvasStencil, &CanvasStencil::GetTexture>()
				)
			);
		}
	}
}