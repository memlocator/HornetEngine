#include "Appearance.h"

#include "Texture.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Appearance>()
		{
			Reflect<Appearance, Object>::Class
			(
				"Appearance",
				{ "GameObject" },

				Member<Bind(&Appearance::BlendTexture)>("BlendTexture"),
				Member<Bind(&Appearance::Color)>("Color"),
				Member<Bind(&Appearance::TextureColor)>("TextureColor"),
				Member<Bind(&Appearance::UVScale)>("UVScale"),
				Member<Bind(&Appearance::UVOffset)>("UVOffset"),
				Member<Bind(&Appearance::Texture)>("Texture")
			);
		}
	}
}