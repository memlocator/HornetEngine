#include "PhysicalMaterial.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<PhysicalMaterial>()
		{
			Reflect<PhysicalMaterial, Object>::Class
			(
				"PhysicalMaterial",
				{ "GameObject" },

				Member<Bind(&PhysicalMaterial::Albedo)>("Albedo"),
				Member<Bind(&PhysicalMaterial::Roughness)>("Roughness"),
				Member<Bind(&PhysicalMaterial::Metalness)>("Metalness"),
				Member<Bind(&PhysicalMaterial::RefractiveIndex)>("RefractiveIndex"),
				Member<Bind(&PhysicalMaterial::Transparency)>("Transparency"),
				Member<Bind(&PhysicalMaterial::Translucency)>("Translucency"),
				Member<Bind(&PhysicalMaterial::Emission)>("Emission")
			);
		}
	}
}