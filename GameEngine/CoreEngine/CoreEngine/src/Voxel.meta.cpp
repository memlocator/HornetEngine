#include "Voxel.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Voxel>()
		{
			Reflect<Voxel, Object>::Class
			(
				"Voxel",
				{ "GameObject" }
			);
		}
	}
}