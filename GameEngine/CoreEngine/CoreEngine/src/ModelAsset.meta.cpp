#include "ModelAsset.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<ModelAsset>()
		{
			Reflect<ModelAsset, Object>::Class
			(
				"ModelAsset",
				{ "GameObject" },

				Function(
					"GetMeshID",
					Overload(
						Const,
						Returns<int>()
					).Bind<ModelAsset, &ModelAsset::GetMeshID>()
				),

				Function(
					"IsCore",
					Overload(
						Const,
						Returns<bool>()
					).Bind<ModelAsset, &ModelAsset::IsCore>()
				),

				Function(
					"IsLoaded",
					Overload(
						Const,
						Returns<bool>()
					).Bind<ModelAsset, &ModelAsset::IsLoaded>()
				),

				Function(
					"IsDying",
					Overload(
						Const,
						Returns<bool>()
					).Bind<ModelAsset, &ModelAsset::IsDying>()
				),

				Function(
					"GetMinimumCorner",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<ModelAsset, &ModelAsset::GetMinimumCorner>()
				),

				Function(
					"GetMaximumCorner",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<ModelAsset, &ModelAsset::GetMaximumCorner>()
				),

				Function(
					"GetCenter",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<ModelAsset, &ModelAsset::GetCenter>()
				),

				Function(
					"GetSize",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<ModelAsset, &ModelAsset::GetSize>()
				),

				Function(
					"Load",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("path"),
						Argument<Enum::VertexMode, Default(Enum::VertexMode::Seperate)>("mode")
					).Bind<ModelAsset, &ModelAsset::Load>()
				),

				Function(
					"Unload",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<ModelAsset, &ModelAsset::Unload>()
				),

				Function(
					"Release",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<ModelAsset, &ModelAsset::Release>()
				)
			);
		}
	}
}