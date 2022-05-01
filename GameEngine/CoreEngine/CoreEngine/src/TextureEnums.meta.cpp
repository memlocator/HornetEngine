#include "Texture.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		template <>
		void ReflectType<Enum::SampleType>()
		{
			Reflect<Enum::SampleType>::Enum
			(
				"SampleType",
				Value<Enum::SampleType::Nearest>("Nearest"),
				Value<Enum::SampleType::Linear>("Linear")
			);
		}

		template <>
		void ReflectType<Enum::WrapType>()
		{
			Reflect<Enum::WrapType>::Enum
			(
				"WrapType",
				Value<Enum::WrapType::Repeat>("Repeat"),
				Value<Enum::WrapType::ClampCutOff>("ClampCutOff"),
				Value<Enum::WrapType::ClampExtend>("ClampExtend")
			);
		}

		template <>
		void ReflectType<Enum::InternalFormat>()
		{
			Reflect<Enum::InternalFormat>::Enum
			(
				"InternalFormat",
				Value<Enum::InternalFormat::Color4>("Color4"),
				Value<Enum::InternalFormat::Depth24Stencil8>("Depth24Stencil8"),
				Value<Enum::InternalFormat::Color416F>("Color416F"),
				Value<Enum::InternalFormat::RGB32F>("RGB32F"),
				Value<Enum::InternalFormat::RGB8>("RGB8"),
				Value<Enum::InternalFormat::RG32F>("RG32F"),
				Value<Enum::InternalFormat::R32F>("R32F")
			);
		}

		template <>
		void ReflectType<Enum::Format>()
		{
			Reflect<Enum::Format>::Enum
			(
				"Format",
				Value<Enum::Format::Color4>("Color4"),
				Value<Enum::Format::RGB>("RGB"),
				Value<Enum::Format::RG>("RG"),
				Value<Enum::Format::Red>("Red"),
				Value<Enum::Format::DepthStencil>("DepthStencil")
			);
		}

		template <>
		void ReflectType<Enum::DataType>()
		{
			Reflect<Enum::DataType>::Enum
			(
				"DataType",
				Value<Enum::DataType::UnsignedByte>("UnsignedByte"),
				Value<Enum::DataType::Float>("Float"),
				Value<Enum::DataType::DepthStencilInt>("DepthStencilInt")
			);
		}
	}
}