#include "GraphicsCorePackage.h"

#include "FrameBuffer.h"
#include "Dimensions.h"
#include "Texture.h"
#include "CubeMap.h"
#include "GameWindow.h"

#undef Static
#undef Reflect
#undef Reflected

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		extern void ReflectType<GraphicsEngine::FrameBuffer>();
		
		template <>
		extern void ReflectType<Dimensions>();
		
		template <>
		extern void ReflectType<GraphicsEngine::Texture>();
		
		template <>
		extern void ReflectType<GraphicsEngine::GameWindow>();
		
		template <>
		extern void ReflectType<CubeMapTexture>();
		
		template <>
		extern void ReflectType<CubeMapBuffer>();

		template <>
		extern void ReflectType<Enum::SampleType>();

		template <>
		extern void ReflectType<Enum::WrapType>();

		template <>
		extern void ReflectType<Enum::InternalFormat>();

		template <>
		extern void ReflectType<Enum::Format>();

		template <>
		extern void ReflectType<Enum::DataType>();

		template <>
		void ReflectPackage<GraphicsCorePackage>()
		{
			ReflectFromPackage<
				GraphicsEngine::FrameBuffer,
				Dimensions,
				CubeMapTexture,
				CubeMapBuffer,
				GraphicsEngine::Texture,
				GraphicsEngine::GameWindow,
				Enum::SampleType,
				Enum::WrapType,
				Enum::InternalFormat,
				Enum::Format,
				Enum::DataType
			>();
		}
	}
}