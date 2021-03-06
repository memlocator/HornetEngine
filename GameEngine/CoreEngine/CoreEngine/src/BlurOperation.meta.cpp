#include "BlurOperation.h"

#include "Texture.h"
#include "FrameBuffer.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<BlurPassOperation>()
		{
			Reflect<BlurPassOperation, RenderOperation>::Class
			(
				"BlurPassOperation",
				{ "GameObject" },

				Member<Bind(&BlurPassOperation::Direction)>("Direction"),
				Member<Bind(&BlurPassOperation::Input)>("Input"),

				Constructor(
					Overload()
				),

				Function(
					"Configure",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const Vector3&>("direction"),
						Argument<const std::shared_ptr<Texture>&>("input")
					).Bind<BlurPassOperation, &BlurPassOperation::Configure>()
				)
			);
		}

		template <>
		void ReflectType<BlurOperation>()
		{
			Reflect<BlurOperation, RenderOperation>::Class
			(
				"BlurOperation",
				{ "GameObject" },

				Member<Bind(&BlurOperation::Radius)>("Radius"),
				Member<Bind(&BlurOperation::Sigma)>("Sigma"),
				Member<Bind(&BlurOperation::Resolution)>("Resolution"),
				Member<Bind(&BlurOperation::Transform)>("Transform"),
				Member<Bind(&BlurOperation::Input)>("Input"),
				Member<Bind(&BlurOperation::Output)>("Output"),
				Member<Bind(&BlurOperation::Detatch)>("Detatch"),

				Constructor(
					Overload()
				),

				Function(
					"Configure",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<int>("width"),
						Argument<int>("height"),
						Argument<Enum::SampleType, Default(Enum::SampleType::Nearest)>("sampleType"),
						Argument<Enum::WrapType, Default(Enum::WrapType::Repeat)>("wrapType"),
						Argument<Enum::DataType, Default(Enum::DataType::UnsignedByte)>("dataType"),
						Argument<Enum::InternalFormat, Default(Enum::InternalFormat::Color4)>("internalFormat"),
						Argument<Enum::Format, Default(Enum::Format::Color4)>("format")
					).Bind<BlurOperation, &BlurOperation::Configure>()
				)
			);
		}
	}
}