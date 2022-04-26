#include "ShadingOperation.h"

#include "FrameBuffer.h"
#include "Camera.h"
#include "Scene.h"
#include "Light.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<ShadingOperation>()
		{
			Reflect<ShadingOperation, RenderOperation>::Class
			(
				"ShadingOperation",
				{ "GameObject" },

				Member<Bind(&ShadingOperation::SceneBuffer)>("SceneBuffer"),
				Member<Bind(&ShadingOperation::LightBuffer)>("LightBuffer"),
				Member<Bind(&ShadingOperation::CurrentCamera)>("CurrentCamera"),
				Member<Bind(&ShadingOperation::CurrentScene)>("CurrentScene"),
				Member<Bind(&ShadingOperation::GlobalLight)>("GlobalLight"),
				Member<Bind(&ShadingOperation::Resolution)>("Resolution"),

				Constructor(
					Overload()
				)
			);
		}
	}
}