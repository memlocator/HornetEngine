#pragma once

#include "Object.h"

namespace GraphicsEngine
{
	class Materials : public Engine::Object
	{
	public:
		virtual ~Materials() {}

		void Initialize();
		void Update(Float) {}
	};

}
