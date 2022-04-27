#pragma once

#include "Vector3.h"
#include "RenderOperation.h"
#include "Texture.h"
#include "Mesh.h"
#include "FrameBuffer.h"

namespace GraphicsEngine
{
	class BlurPassOperation : public RenderOperation
	{
	public:
		Vector3 Direction;
		std::weak_ptr<Texture> Input;

		void Configure(const Vector3& direction, const std::shared_ptr<Texture>& input);

		void Render();
	};
}

namespace GraphicsEngine
{
	class BlurOperation : public RenderOperation
	{
	public:
		int Radius = 1;
		float Sigma = 1;
		Vector3 Resolution;
		Matrix3 Transform;
		std::weak_ptr<Texture> Input;
		std::weak_ptr<FrameBuffer> Output;
		bool Detatch = true;

		void Initialize();

		typedef Enum::SampleType ESampleType;
		typedef Enum::WrapType EWrapType;
		typedef Enum::InternalFormat EInternalFormat;
		typedef Enum::Format EFormat;
		typedef Enum::DataType EDataType;

		void Configure(int width, int height, ESampleType sampleType = ESampleType::Nearest, EWrapType wrapType = EWrapType::Repeat, EDataType dataType = EDataType::UnsignedByte, EInternalFormat internalFormat = EInternalFormat::RGBA, EFormat format = EFormat::RGBA);

		void SetInput(const std::shared_ptr<Texture>& texture);
		void Render();
		std::shared_ptr<FrameBuffer> GetHorizontalPass() const;

	private:
		std::weak_ptr<FrameBuffer> HorizontalBuffer;
		std::weak_ptr<BlurPassOperation> HorizontalPass;
		std::weak_ptr<BlurPassOperation> VerticalPass;
	};
}
