#pragma once

#include "Object.h"
#include "ColliderData.h"

namespace Engine
{
	namespace Physics
	{
		class ColliderAsset : public Object
		{
		public:
			ColliderData Data;

			~ColliderAsset() {}

			void ConfigureTriangleMesh();
			void ConfigureSquareMesh();
			void ConfigureOctagonMesh();
			void ConfigureShipMesh();
			void ConfigureChargerShieldMesh();
			void ConfigureWormHeadMesh();
			void ConfigureWormTailMesh();
		};
	}
}