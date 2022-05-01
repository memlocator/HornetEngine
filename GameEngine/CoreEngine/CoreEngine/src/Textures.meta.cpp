#include "Textures.h"

#include "Texture.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Textures>()
		{
			Reflect<Textures, Object>::Class
			(
				"Textures",
				{ "GameObject" },

				Constructor(
					Overload()
				),

				Function(
					"Create",
					Overload(
						Static,
						Returns<std::shared_ptr<Texture>>(),
						Argument<int>("width"),
						Argument<int>("height"),
						Argument<Enum::SampleType, Default(Enum::SampleType::Nearest)>("sampleType"),
						Argument<Enum::WrapType, Default(Enum::WrapType::Repeat)>("wrapType"),
						Argument<Enum::DataType, Default(Enum::DataType::UnsignedByte)>("dataType"),
						Argument<Enum::InternalFormat, Default(Enum::InternalFormat::Color4)>("internalFormat"),
						Argument<Enum::Format, Default(Enum::Format::Color4)>("format"),
						Argument<bool, Default(false)>("invertedY")
					).Bind<&Textures::Create>(),
					Overload(
						Static,
						Returns<std::shared_ptr<Texture>>(),
						Argument<const std::string&>("fileName"),
						Argument<Enum::SampleType, Default(Enum::SampleType::Nearest)>("sampleType"),
						Argument<Enum::WrapType, Default(Enum::WrapType::Repeat)>("wrapType"),
						Argument<Enum::DataType, Default(Enum::DataType::UnsignedByte)>("dataType"),
						Argument<Enum::InternalFormat, Default(Enum::InternalFormat::Color4)>("internalFormat"),
						Argument<Enum::Format, Default(Enum::Format::Color4)>("format")
					).Bind<&Textures::Create>()
				),

				Function(
					"Add",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<Texture>&>("texture"),
						Argument<const std::string&>("name")
					).Bind<Textures, &Textures::Add>()
				),

				Function(
					"LoadDirectory",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("folderPath"),
						Argument<Enum::SampleType, Default(Enum::SampleType::Nearest)>("sampleType"),
						Argument<Enum::WrapType, Default(Enum::WrapType::Repeat)>("wrapType"),
						Argument<Enum::DataType, Default(Enum::DataType::UnsignedByte)>("dataType"),
						Argument<Enum::InternalFormat, Default(Enum::InternalFormat::Color4)>("internalFormat"),
						Argument<Enum::Format, Default(Enum::Format::Color4)>("format")
					).Bind<Textures, &Textures::LoadDirectory>()
				)
			);
		}
	}
}