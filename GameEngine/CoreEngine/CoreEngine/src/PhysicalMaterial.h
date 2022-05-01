#pragma once

#include "Color4.h"
#include "Object.h"

namespace GraphicsEngine
{
	class PhysicalMaterial : public Engine::Object
	{
	public:
		Color4 Albedo = Color4(1.f, 1.f, 1.f, 0.f);
		float Roughness = 0.5f;
		float Metalness = 0;
		float RefractiveIndex = 1.1f;
		float Transparency = 0;
		float Translucency = 0.01f;
		float Emission = 0;
	};
}