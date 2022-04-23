#include "GraphicsOperationPackage.h"

#include "RenderOperation.h"
#include "BlurOperation.h"
#include "DrawSceneOperation.h"
#include "GlowingSceneOperation.h"
#include "HDRColorCorrectionOperation.h"
#include "InterfaceDrawOperation.h"
#include "ShadingOperation.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		extern void ReflectType<GraphicsEngine::RenderOperation>();
		
		template <>
		extern void ReflectType<GraphicsEngine::BlurPassOperation>();
		
		template <>
		extern void ReflectType<GraphicsEngine::BlurOperation>();
		
		template <>
		extern void ReflectType<GraphicsEngine::DrawSceneOperation>();
		
		template <>
		extern void ReflectType<GraphicsEngine::GlowingSceneOperation>();
		
		template <>
		extern void ReflectType<GraphicsEngine::HDRColorCorrectionOperation>();
		
		template <>
		extern void ReflectType<GraphicsEngine::InterfaceDrawOperation>();
		
		template <>
		extern void ReflectType<GraphicsEngine::ShadingOperation>();
		
		template <>
		extern void ReflectType<Enum::LuminescenceMode>();

		template <>
		void ReflectPackage<GraphicsOperationPackage>()
		{
			ReflectFromPackage<
				GraphicsEngine::RenderOperation,
				GraphicsEngine::BlurPassOperation,
				GraphicsEngine::BlurOperation,
				GraphicsEngine::DrawSceneOperation,
				GraphicsEngine::GlowingSceneOperation,
				GraphicsEngine::HDRColorCorrectionOperation,
				GraphicsEngine::InterfaceDrawOperation,
				GraphicsEngine::ShadingOperation,
				Enum::LuminescenceMode,
				Enum::RangeFittingMode
			>();
		}
	}
}