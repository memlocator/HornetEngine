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
				Value<Enum::InternalFormat::RGBA>("RGBA")
			);
		}

		template <>
		void ReflectType<Enum::Format>()
		{
			Reflect<Enum::Format>::Enum
			(
				"Format",
				Value<Enum::Format::RGBA>("RGBA")
			);
		}

		template <>
		void ReflectType<Enum::DataType>()
		{
			Reflect<Enum::DataType>::Enum
			(
				"DataType",
				Value<Enum::DataType::UnsignedByte>("UnsignedByte"),
				Value<Enum::DataType::Float>("Float")
			);
		}
	}
}