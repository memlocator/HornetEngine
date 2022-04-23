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

				Function(
					"Create",
					Overload(
						Static,
						Returns<std::shared_ptr<Texture>>(),
						Argument<int>("width"),
						Argument<int>("height"),
						Argument<GLint, Default(Enum::SampleType::Nearest)>("sampleType"),
						Argument<GLint, Default(Enum::WrapType::Repeat)>("wrapType"),
						Argument<GLenum, Default(Enum::DataType::UnsignedByte)>("dataType"),
						Argument<GLint, Default(Enum::InternalFormat::RGBA)>("internalFormat"),
						Argument<GLenum, Default(Enum::Format::RGBA)>("format"),
						Argument<bool, Default(false)>("invertedY")
					).Bind<&Textures::Create>(),
					Overload(
						Static,
						Returns<std::shared_ptr<Texture>>(),
						Argument<const std::string&>("fileName"),
						Argument<GLint, Default(Enum::SampleType::Nearest)>("sampleType"),
						Argument<GLint, Default(Enum::WrapType::Repeat)>("wrapType"),
						Argument<GLenum, Default(Enum::DataType::UnsignedByte)>("dataType"),
						Argument<GLint, Default(Enum::InternalFormat::RGBA)>("internalFormat"),
						Argument<GLenum, Default(Enum::Format::RGBA)>("format")
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
						Argument<GLint, Default(Enum::SampleType::Nearest)>("sampleType"),
						Argument<GLint, Default(Enum::WrapType::Repeat)>("wrapType"),
						Argument<GLenum, Default(Enum::DataType::UnsignedByte)>("dataType"),
						Argument<GLint, Default(Enum::InternalFormat::RGBA)>("internalFormat"),
						Argument<GLenum, Default(Enum::Format::RGBA)>("format")
					).Bind<Textures, &Textures::LoadDirectory>()
				)
			);
		}
	}
}