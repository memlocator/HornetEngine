#pragma once

#include <vector>
#include <memory>

#include "Precision.h"

namespace GraphicsEngine
{
	class Camera;
	class Light;

	class LightBuffer
	{
	public:
		std::weak_ptr<Camera> CurrentCamera;

		void PushLight(const std::shared_ptr<Light>& light);
		void Flush() const;
		void Clear();

	private:
		typedef std::vector<Float> FloatVector;
		typedef std::vector<int> IntVector;

		FloatVector Attenuation;
		FloatVector Position;
		FloatVector Direction;
		FloatVector Diffuse;
		FloatVector Specular;
		FloatVector Ambient;
		FloatVector SpotlightAngles;
		IntVector SpotlightFalloff;
		IntVector Type;
	};
}