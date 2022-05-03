#pragma once

#include "Object.h"
#include "Math/Color4.h"
#include "Math/Vector3.h"

namespace GraphicsEngine
{
	class Texture;

	class Appearance : public Engine::Object
	{
	public:
		bool BlendTexture = true;
		Color4 Color;
		Color4 TextureColor;
		Vector3 UVScale = Vector3(1, 1);
		Vector3 UVOffset = Vector3(0, 0);
		std::weak_ptr<Texture> Texture;

		~Appearance() {}
	};
}
