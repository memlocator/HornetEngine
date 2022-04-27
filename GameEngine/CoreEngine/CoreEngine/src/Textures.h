#pragma once

#include <vector>
#include <map>
#include <glew.h>

#include "Object.h"
#include "Texture.h"

namespace GraphicsEngine
{
	class Texture;

	class Textures : public Engine::Object
	{
	public:
		~Textures() {}

		typedef Enum::SampleType ESampleType;
		typedef Enum::WrapType EWrapType;
		typedef Enum::InternalFormat EInternalFormat;
		typedef Enum::Format EFormat;
		typedef Enum::DataType EDataType;

		static std::shared_ptr<Texture> Create(int width, int height, ESampleType sampleType = ESampleType::Nearest, EWrapType wrapType = EWrapType::Repeat, EDataType dataType = EDataType::UnsignedByte, EInternalFormat internalFormat = EInternalFormat::RGBA, EFormat format = EFormat::RGBA, bool invertedY = false);
		static std::shared_ptr<Texture> Create(const std::string& fileName, ESampleType sampleType = ESampleType::Nearest, EWrapType wrapType = EWrapType::Repeat, EDataType dataType = EDataType::UnsignedByte, EInternalFormat internalFormat = EInternalFormat::RGBA, EFormat format = EFormat::RGBA);
		static std::shared_ptr<Texture> Create(int width, int height, unsigned char* pixelData, ESampleType sampleType = ESampleType::Nearest, EWrapType wrapType = EWrapType::Repeat, EDataType dataType = EDataType::UnsignedByte, EInternalFormat internalFormat = EInternalFormat::RGBA, EFormat format = EFormat::RGBA, bool invertedY = false);

		void LoadDirectory(const std::string& folderPath, ESampleType sampleType = ESampleType::Nearest, EWrapType wrapType = EWrapType::Repeat, EDataType dataType = EDataType::UnsignedByte, EInternalFormat internalFormat = EInternalFormat::RGBA, EFormat format = EFormat::RGBA);

		void Add(const std::shared_ptr<Texture>& texture, const std::string& name);
	};
}
