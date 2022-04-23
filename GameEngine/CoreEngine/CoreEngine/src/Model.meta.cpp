#include "Model.h"

#include "ModelAsset.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Model>()
		{
			Reflect<Model, SceneObject>::Class
			(
				"Model",
				{ "GameObject" },

				Member<Bind(&Model::Reflectivity)>("Reflectivity"),
				Member<Bind(&Model::Color)>("Color"),
				Member<Bind(&Model::GlowColor)>("GlowColor"),
				Member<Bind(&Model::Asset)>("Asset"),

				Function(
					"GetMeshName",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Model, &Model::GetMeshName>()
				)
			);
		}
	}
}