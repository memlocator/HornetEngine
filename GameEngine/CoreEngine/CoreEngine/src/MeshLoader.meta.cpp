#include "MeshLoader.h"

#include "ModelAsset.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<MeshLoader>()
		{
			Reflect<MeshLoader, Object>::Class
			(
				"MeshLoader",
				{ "GameObject" },

				Function(
					"NewAsset",
					Overload(
						Static,
						Returns<std::shared_ptr<Engine::ModelAsset>>(),
						Argument<const std::string&>("name")
					).Bind<&MeshLoader::NewAsset>(),
					Overload(
						Static,
						Returns<std::shared_ptr<Engine::ModelAsset>>(),
						Argument<const std::string&>("name"),
						Argument<const std::string&>("path"),
						Argument<Enum::VertexMode, Default(Enum::VertexMode::Seperate)>("mode")
					).Bind<&MeshLoader::NewAsset>()
				)
			);
		}
	}
}