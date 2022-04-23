#include "Material.h"

#include "Texture.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Material>()
		{
			Reflect<Material, Object>::Class
			(
				"Material",
				{ "GameObject" },

				Member<Bind(&Material::Diffuse)>("Diffuse"),
				Member<Bind(&Material::Specular)>("Specular"),
				Member<Bind(&Material::Ambient)>("Ambient"),
				Member<Bind(&Material::Emission)>("Emission"),
				Member<Bind(&Material::Shininess)>("Shininess"),

				Member<Bind(&Material::TextureColor)>("TextureColor"),
				Member<Bind(&Material::BlendTexture)>("BlendTexture"),
				Member<Bind(&Material::UVScale)>("UVScale"),
				Member<Bind(&Material::UVOffset)>("UVOffset"),
				Member<Bind(&Material::BoxScale)>("BoxScale"),
				Member<Bind(&Material::CubeMapped)>("CubeMapped"),
				Member<Bind(&Material::FlipCubeMapV)>("FlipCubeMapV"),
				Member<Bind(&Material::CompressedNormalMap)>("CompressedNormalMap"),
				Member<Bind(&Material::UseOffsetMap)>("UseOffsetMap"),

				Member<Bind(&Material::NormalMap)>("NormalMap"),
				Member<Bind(&Material::SpecularMap)>("SpecularMap"),
				Member<Bind(&Material::GlowMap)>("GlowMap"),
				Member<Bind(&Material::CubeMapTop)>("CubeMapTop"),
				Member<Bind(&Material::CubeMapBottom)>("CubeMapBottom"),
				Member<Bind(&Material::CubeMapLeft)>("CubeMapLeft"),
				Member<Bind(&Material::CubeMapRight)>("CubeMapRight"),
				Member<Bind(&Material::CubeMapFront)>("CubeMapFront"),
				Member<Bind(&Material::CubeMapBack)>("CubeMapBack"),
				Member<Bind(&Material::DiffuseTexture)>("DiffuseTexture"),

				Function(
					"GetMaterialId",
					Overload(
						Const,
						Returns<int>()
					).Bind<Material, &Material::GetMaterialId>()
				)
			);
		}
	}
}