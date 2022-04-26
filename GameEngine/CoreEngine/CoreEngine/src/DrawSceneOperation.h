#pragma once

#include "RenderOperation.h"
#include "Scene.h"

namespace GraphicsEngine
{
	class DrawSceneOperation : public RenderOperation
	{
	public:
		std::weak_ptr<Scene> CurrentScene;

		void Configure(const std::shared_ptr<Scene>& scene);

		void Render();
	};
}
