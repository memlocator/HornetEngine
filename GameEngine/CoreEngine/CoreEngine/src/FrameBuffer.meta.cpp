#include "FrameBuffer.h"\

#include "Texture.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<FrameBuffer>()
		{
			Reflect<FrameBuffer, Object>::Class
			(
				"FrameBuffer",
				{ "GameObject" },

				Member<Bind(&FrameBuffer::WindowSize)>("WindowSize"),

				Function(
					"DrawTo",
					Overload(
						Const,
						Returns<void>(),
						Argument<int, Default(0)>("x"),
						Argument<int, Default(0)>("y"),
						Argument<int, Default(-1)>("width"),
						Argument<int, Default(-1)>("height")
					).Bind<FrameBuffer, &FrameBuffer::DrawTo>()
				),

				Function(
					"Bind",
					Overload(
						Const,
						Returns<void>()
					).Bind<FrameBuffer, &FrameBuffer::Bind>()
				),

				Function(
					"Resize",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<int>("width"),
						Argument<int>("height"),
						Argument<bool, Default(true)>("resizeTextures")
					).Bind<FrameBuffer, &FrameBuffer::Resize>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<Dimensions>("newSize"),
						Argument<bool, Default(true)>("resizeTextures")
					).Bind<FrameBuffer, &FrameBuffer::Resize>()
				),

				Function(
					"GetTexture",
					Overload(
						Const,
						Returns<std::shared_ptr<Texture>>(),
						Argument<unsigned int, Default(0)>("attachmentSlot")
					).Bind<FrameBuffer, &FrameBuffer::GetTexture>()
				),

				Function(
					"GetDepthTexture",
					Overload(
						Const,
						Returns<std::shared_ptr<Texture>>()
					).Bind<FrameBuffer, &FrameBuffer::GetDepthTexture>()
				),

				Function(
					"GetAttachmentSlot",
					Overload(
						Const,
						Returns<GLenum>(),
						Argument<unsigned int, Default(0)>("attachmentSlot")
					).Bind<FrameBuffer, &FrameBuffer::GetAttachmentSlot>()
				),

				Function(
					"GetID",
					Overload(
						Const,
						Returns<GLuint>()
					).Bind<FrameBuffer, &FrameBuffer::GetID>()
				),

				Function(
					"GetSize",
					Overload(
						Const,
						Returns<Dimensions>()
					).Bind<FrameBuffer, &FrameBuffer::GetSize>()
				),

				Function(
					"SetAttachmentCount",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<unsigned int>("attachments")
					).Bind<FrameBuffer, &FrameBuffer::SetAttachmentCount>()
				),

				Function(
					"AttachTexture",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<unsigned int>("attachmentSlot"),
						Argument<const std::shared_ptr<Texture>&>("texture"),
						Argument<GLenum>("attachment"),
						Argument<bool, Default(false)>("setParent"),
						Argument<GLenum, Default(GL_TEXTURE_2D)>("type")
					).Bind<FrameBuffer, &FrameBuffer::AttachTexture>()
				),

				Function(
					"BindAttachments",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<FrameBuffer, &FrameBuffer::BindAttachments>()
				),

				Function(
					"ClearTextures",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<FrameBuffer, &FrameBuffer::ClearTextures>()
				),

				Function(
					"GetWidth",
					Overload(
						Const,
						Returns<int>()
					).Bind<FrameBuffer, &FrameBuffer::GetWidth>()
				),

				Function(
					"GetHeight",
					Overload(
						Const,
						Returns<int>()
					).Bind<FrameBuffer, &FrameBuffer::GetHeight>()
				),

				Function(
					"DisableDepthBuffer",
					Overload(
						Mutable,
						Returns<void>()
					).Bind<FrameBuffer, &FrameBuffer::DisableDepthBuffer>()
				),

				Function(
					"SetViewport",
					Overload(
						Static,
						Returns<void>(),
						Argument<int>("x"),
						Argument<int>("y"),
						Argument<int>("width"),
						Argument<int>("height")
					).Bind<&FrameBuffer::SetViewport>()
				),

				Function(
					"Detatch",
					Overload(
						Static,
						Returns<void>()
					).Bind<&FrameBuffer::Detatch>()
				),

				Function(
					"GetAttachedBuffer",
					Overload(
						Static,
						Returns<std::shared_ptr<FrameBuffer>>()
					).Bind<&FrameBuffer::GetAttachedBuffer>()
				),

				Function(
					"Create",
					Overload(
						Static,
						Returns<std::shared_ptr<FrameBuffer>>(),
						Argument<unsigned int>("width"),
						Argument<unsigned int>("height"),
						Argument<const std::shared_ptr<Texture>&>("colorBuffer0"),
						Argument<bool, Default(false)>("setParent"),
						Argument<bool, Default(true)>("depthBufferEnabled")
					).Bind<&FrameBuffer::Create>()
				)
			);
		}
	}
}