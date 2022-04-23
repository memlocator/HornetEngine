#include "CubeMap.h"

#include "FrameBuffer.h"
#include "Texture.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<CubeMapTexture>()
		{
			Reflect<CubeMapTexture, Object>::Class
			(
				"CubeMapTexture",
				{ "GameObject" },

				Member<Bind(&CubeMapTexture::Front)>("Front"),
				Member<Bind(&CubeMapTexture::Back)>("Back"),
				Member<Bind(&CubeMapTexture::Left)>("Left"),
				Member<Bind(&CubeMapTexture::Right)>("Right"),
				Member<Bind(&CubeMapTexture::Top)>("Top"),
				Member<Bind(&CubeMapTexture::Bottom)>("Bottom")
			);
		}

		template <>
		void ReflectType<CubeMapBuffer>()
		{
			Reflect<CubeMapBuffer, Object>::Class
			(
				"CubeMapBuffer",
				{ "GameObject" },

				Member<Bind(&CubeMapBuffer::Front)>("Front"),
				Member<Bind(&CubeMapBuffer::Back)>("Back"),
				Member<Bind(&CubeMapBuffer::Left)>("Left"),
				Member<Bind(&CubeMapBuffer::Right)>("Right"),
				Member<Bind(&CubeMapBuffer::Top)>("Top"),
				Member<Bind(&CubeMapBuffer::Bottom)>("Bottom")
			);
		}
	}
}