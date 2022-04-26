#include "Scene.h"

#include "Camera.h"
#include "Light.h"
#include "Terrain.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Scene>()
		{
			Reflect<Scene, Object>::Class
			(
				"Scene",
				{ "GameObject" },

				Member<Bind(&Scene::CurrentCamera)>("CurrentCamera"),
				Member<Bind(&Scene::GlobalLight)>("GlobalLight"),

				Member<Bind(&Scene::FogColor)>("FogColor"),
				Member<Bind(&Scene::FogNear)>("FogNear"),
				Member<Bind(&Scene::FogFar)>("FogFar"),

				Member<Bind(&Scene::GlobalDiffuse)>("GlobalDiffuse"),
				Member<Bind(&Scene::GlobalSpecular)>("GlobalSpecular"),
				Member<Bind(&Scene::GlobalAmbient)>("GlobalAmbient"),

				Constructor(
					Overload()
				),

				Function(
					"RefreshWatches",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<Scene, &Scene::RefreshWatches>()
				),

				Function(
					"ClearStaticObjects",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<Scene, &Scene::ClearStaticObjects>()
				),

				Function(
					"CastRay",
					LuaOverload<Scene, &Scene::CastRay>()
				),

				Function(
					"AddObject",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<SceneObject>&>("object")
					).Bind<Scene, &Scene::AddObject>()
				),

				Function(
					"AddLight",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Light>&>("light")
					).Bind<Scene, &Scene::AddLight>()
				),

				Function(
					"AddTerrain",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Engine::Terrain>&>("terrain")
					).Bind<Scene, &Scene::AddTerrain>()
				),

				Function(
					"RemoveObject",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<SceneObject>&>("object")
					).Bind<Scene, &Scene::RemoveObject>()
				),

				Function(
					"RemoveLight",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Light>&>("light")
					).Bind<Scene, &Scene::RemoveLight>()
				),

				Function(
					"RemoveTerrain",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Engine::Terrain>&>("terrain")
					).Bind<Scene, &Scene::RemoveTerrain>()
				),

				Function(
					"GetLights",
					Overload(
						Const,
						Returns<int>()
					).Bind<Scene, &Scene::GetLights>()
				),

				Function(
					"GetLight",
					Overload(
						Const,
						Returns<std::shared_ptr<Light>>(),
						Argument<int>("index")
					).Bind<Scene, &Scene::GetLight>()
				),

				Function(
					"GetObjects",
					Overload(
						Const,
						Returns<int>()
					).Bind<Scene, &Scene::GetObjects>()
				),

				Function(
					"GetObject",
					Overload(
						Const,
						Returns<std::shared_ptr<SceneObject>>(),
						Argument<int>("index")
					).Bind<Scene, &Scene::GetObject>()
				),

				Function(
					"BuildRenderQueue",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<GraphicsEngine::Camera>&>("targetCamera")
					).Bind<Scene, &Scene::BuildRenderQueue>()
				),

				Function(
					"DrawQueued",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<bool, Default(false)>("drawTransparent")
					).Bind<Scene, &Scene::DrawQueued>()
				),

				Function(
					"DrawTerrain",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<bool>("drawLiquid"),
						Argument<const std::shared_ptr<GraphicsEngine::Camera>&>("targetCamera")
					).Bind<Scene, &Scene::DrawTerrain>()
				),

				Function(
					"Draw",
					Overload(
						Const,
						Returns<void>(),
						Argument<bool>("drawTransparent"),
						Argument<const std::shared_ptr<GraphicsEngine::Camera>&>("targetCamera")
					).Bind<Scene, &Scene::Draw>()
				)//,

				//Function(
				//	"Update",
				//	Overload(
				//		Mutable,
				//		Returns<void>(),
				//		Argument<int>("object")
				//	).Bind<Scene, &Scene::Update>(),
				//	Overload(
				//		Mutable,
				//		Returns<void>(),
				//		Argument<int>("object"),
				//		Argument<bool>("isStatic")
				//	).Bind<Scene, &Scene::Update>()
				//)
			);
		}
	}
}