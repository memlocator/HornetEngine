#include "Texture.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Texture>()
		{
			Reflect<Texture, Object>::Class
			(
				"Texture",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Function(
					"Resize",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<int>("width"),
						Argument<int>("height")
					).Bind<Texture, &Texture::Resize>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<Dimensions>("size")
					).Bind<Texture, &Texture::Resize>()
				),

				Function(
					"Load",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<int>("width"),
						Argument<int>("height"),
						Argument<Enum::SampleType, Default(Enum::SampleType::Nearest)>("sampleType"),
						Argument<Enum::WrapType, Default(Enum::WrapType::Repeat)>("wrapType"),
						Argument<Enum::DataType, Default(Enum::DataType::UnsignedByte)>("dataType"),
						Argument<Enum::InternalFormat, Default(Enum::InternalFormat::Color4)>("internalFormat"),
						Argument<Enum::Format, Default(Enum::Format::Color4)>("format"),
						Argument<bool, Default(false)>("invertedY")
					).Bind<Texture, &Texture::Load>(),
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("fileName"),
						Argument<Enum::SampleType, Default(Enum::SampleType::Nearest)>("sampleType"),
						Argument<Enum::WrapType, Default(Enum::WrapType::Repeat)>("wrapType"),
						Argument<Enum::DataType, Default(Enum::DataType::UnsignedByte)>("dataType"),
						Argument<Enum::InternalFormat, Default(Enum::InternalFormat::Color4)>("internalFormat"),
						Argument<Enum::Format, Default(Enum::Format::Color4)>("format"),
						Argument<bool, Default(false)>("isDXT5")
					).Bind<Texture, &Texture::Load>()
				),

				Function(
					"GetTextureID",
					Overload(
						Const,
						Returns<GLuint>()
					).Bind<Texture, &Texture::GetTextureID>()
				),

				Function(
					"GetWidth",
					Overload(
						Const,
						Returns<int>()
					).Bind<Texture, &Texture::GetWidth>()
				),

				Function(
					"GetHeight",
					Overload(
						Const,
						Returns<int>()
					).Bind<Texture, &Texture::GetHeight>()
				),

				Function(
					"GetResolution",
					Overload(
						Const,
						Returns<Vector3>()
					).Bind<Texture, &Texture::GetResolution>()
				),

				Function(
					"GetPixel",
					Overload(
						Const,
						Returns<Color4>(),
						Argument<int>("x"),
						Argument<int>("y")
					).Bind<Texture, &Texture::GetPixel>()
				),

				Function(
					"HasInvertedY",
					Overload(
						Const,
						Returns<bool>()
					).Bind<Texture, &Texture::HasInvertedY>()
				),

				Function(
					"LoadPiece",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("fileName"),
						Argument<int>("x"),
						Argument<int>("y"),
						Argument<int>("width"),
						Argument<int>("height"),
						Argument<Enum::DataType, Default(Enum::DataType::UnsignedByte)>("dataType"),
						Argument<Enum::Format, Default(Enum::Format::Color4)>("format")
					).Bind<Texture, &Texture::LoadPiece>()
				)
			);
		}
	}
}