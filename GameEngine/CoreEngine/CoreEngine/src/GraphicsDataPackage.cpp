#include "GraphicsDataPackage.h"

#include "Fonts.h"
#include "Materials.h"
#include "MeshLoader.h"
#include "Textures.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		extern void ReflectType<GraphicsEngine::Fonts>();
		
		template <>
		extern void ReflectType<GraphicsEngine::Materials>();
		
		template <>
		extern void ReflectType<GraphicsEngine::Textures>();
		
		template <>
		extern void ReflectType<MeshLoader>();

		template <>
		void ReflectPackage<GraphicsDataPackage>()
		{
			ReflectFromPackage<
				GraphicsEngine::Fonts,
				GraphicsEngine::Materials,
				GraphicsEngine::Textures,
				MeshLoader
			>();
		}
	}
}