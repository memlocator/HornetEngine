#pragma once

#include "Object.h"
#include "Math/Vector3.h"

namespace Engine
{
	namespace Physics
	{
		class PointMass : public Object
		{
		public:
			~PointMass() {}

			Float Mass = 1;
			Vector3 Position;
		};
	}
}