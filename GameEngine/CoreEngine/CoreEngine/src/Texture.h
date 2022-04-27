#pragma once

#include <string>
extern "C" {
#include "glew.h"
}

#include "Vector3.h"
#include "RGBA.h"
#include "Object.h"
#include "Dimensions.h"

std::ostream& operator<<(std::ostream& out, const Dimensions& dimensions);

namespace GraphicsEngine
{
	class Texture : public Engine::Object
	{
	public:
		struct SampleTypeEnum
		{
			enum SampleType
			{
				Nearest = GL_NEAREST,
				Linear = GL_LINEAR
			};
		};

		struct WrapTypeEnum
		{
			enum WrapType
			{ 
				Repeat = GL_REPEAT,
				ClampCutOff = GL_CLAMP_TO_BORDER,
				ClampExtend = GL_CLAMP_TO_EDGE
			};
		};

		struct InternalFormatEnum
		{
			enum InternalFormat
			{
				RGBA = GL_RGBA,
				Depth24Stencil8 = GL_DEPTH24_STENCIL8,
				RGBA16F = GL_RGBA16F,
				RGB32F = GL_RGB32F,
				RGB8 = GL_RGB8,
				RG32F = GL_RG32F,
				R32F = GL_R32F
			};
		};

		struct FormatEnum
		{
			enum Format
			{
				RGBA = GL_RGBA,
				RGB = GL_RGB,
				RG = GL_RG,
				Red = GL_RED,
				DepthStencil = GL_DEPTH_STENCIL
			};
		};

		struct DataTypeEnum
		{
			enum DataType
			{
				UnsignedByte = GL_UNSIGNED_BYTE,
				Float = GL_FLOAT,
				DepthStencilInt = GL_UNSIGNED_INT_24_8
			};
		};

		typedef SampleTypeEnum::SampleType ESampleType;
		typedef WrapTypeEnum::WrapType EWrapType;
		typedef InternalFormatEnum::InternalFormat EInternalFormat;
		typedef FormatEnum::Format EFormat;
		typedef DataTypeEnum::DataType EDataType;

		~Texture();

		void Resize(int width, int height);
		void Resize(Dimensions size);
		void Load(int width, int height, ESampleType sampleType = ESampleType::Nearest, EWrapType wrapType = EWrapType::Repeat, EDataType dataType = EDataType::UnsignedByte , EInternalFormat internalFormat = EInternalFormat::RGBA, EFormat format = EFormat::RGBA, bool invertedY = false);
		void Load(const std::string& fileName, ESampleType sampleType = ESampleType::Nearest, EWrapType wrapType = EWrapType::Repeat, EDataType dataType = EDataType::UnsignedByte, EInternalFormat internalFormat = EInternalFormat::RGBA, EFormat format = EFormat::RGBA, bool isDXT5 = false);
		void Load(int width, int height, unsigned char* pixelData, ESampleType sampleType = ESampleType::Nearest, EWrapType wrapType = EWrapType::Repeat, EDataType dataType = EDataType::UnsignedByte, EInternalFormat internalFormat = EInternalFormat::RGBA, EFormat format = EFormat::RGBA, bool invertedY = false);
		void Upload(int width, int height, void* pixelData, EDataType dataType = EDataType::UnsignedByte, EInternalFormat internalFormat = EInternalFormat::RGBA, EFormat format = EFormat::RGBA);
		GLuint GetTextureID() const;
		int GetWidth() const;
		int GetHeight() const;
		Vector3 GetResolution() const;
		unsigned char* GetPixelData();
		RGBA GetPixel(int x, int y) const;
		bool HasInvertedY() const;

		void LoadPiece(const std::string& fileName, int x, int y, int width, int height, EDataType dataType = EDataType::UnsignedByte, EFormat format = EFormat::RGBA);

	private:
		GLint SampleType = GL_NEAREST;
		GLint WrapType = GL_REPEAT;
		GLenum DataType = GL_UNSIGNED_BYTE;
		GLint InternalFormat = GL_RGBA;
		GLenum Format = GL_RGBA;

		bool IsDXT5nm = false;
		bool InvertedY = false;
		GLuint TextureID = 0;
		Dimensions Size;
		unsigned char* PixelData = nullptr;
		bool StbTexture = false;
	};
}

namespace Enum
{
	typedef GraphicsEngine::Texture::SampleTypeEnum::SampleType SampleType;
	typedef GraphicsEngine::Texture::WrapTypeEnum::WrapType WrapType;
	typedef GraphicsEngine::Texture::InternalFormatEnum::InternalFormat InternalFormat;
	typedef GraphicsEngine::Texture::FormatEnum::Format Format;
	typedef GraphicsEngine::Texture::DataTypeEnum::DataType DataType;
}