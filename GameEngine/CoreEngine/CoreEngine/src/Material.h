#pragma once

#include "Color4.h"
#include "Object.h"
#include "IdentifierHeap.h"

namespace GraphicsEngine
{
	class Texture;

	class Material : public Engine::Object
	{
	public:
		~Material();

		void Initialize();

		Color4 Diffuse = Color4(0.5f, 0.5f, 0.5f, 1);
		Color4 Specular = Color4(0.5f, 0.5f, 0.5f, 1);
		Color4 Ambient = Color4(0.1f, 0.1f, 0.1f, 1);
		Color4 Emission = Color4(0.f, 0.f, 0.f, 0.f);
		int Shininess = 1;

		Color4 TextureColor;
		bool BlendTexture = true;
		Vector3 UVScale = Vector3(1, 1);
		Vector3 UVOffset;
		Vector3 BoxScale = Vector3(1, 1, 1);
		bool CubeMapped = false;
		bool FlipCubeMapV = false;
		bool CompressedNormalMap = false;
		bool UseOffsetMap = false;

		std::weak_ptr<Texture> NormalMap;
		std::weak_ptr<Texture> SpecularMap;
		std::weak_ptr<Texture> GlowMap;
		std::weak_ptr<Texture> CubeMapTop;
		std::weak_ptr<Texture> CubeMapBottom;
		std::weak_ptr<Texture> CubeMapLeft;
		std::weak_ptr<Texture> CubeMapRight;
		std::weak_ptr<Texture> CubeMapFront;
		std::weak_ptr<Texture> CubeMapBack;
		std::weak_ptr<Texture> DiffuseTexture;

		int GetMaterialId() const { return MaterialId; }
		static int GetMaterialCount() { return MaterialRegistry.Size(); }
		static Material* GetMaterialFromId(int id);

	private:
		static IDHeap<Material*> MaterialRegistry;

		int MaterialId = -1;
	};
}
