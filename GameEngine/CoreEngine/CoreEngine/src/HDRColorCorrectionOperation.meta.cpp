#include "HDRColorCorrectionOperation.h"

#include "Texture.h"
#include "FrameBuffer.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Enum::LuminescenceMode>()
		{
			Reflect<Enum::LuminescenceMode>::Enum
			(
				"LuminescenceMode",
				Value<Enum::LuminescenceMode::Photometric>("Photometric"),
				Value<Enum::LuminescenceMode::Digital>("Digital"),
				Value<Enum::LuminescenceMode::DigitalAccurate>("DigitalAccurate")
			);
		}

		template <>
		void ReflectType<Enum::RangeFittingMode>()
		{
			Reflect<Enum::RangeFittingMode>::Enum
			(
				"RangeFittingMode",
				Value<Enum::RangeFittingMode::Exposure>("Exposure"),
				Value<Enum::RangeFittingMode::Burnout>("Burnout"),
				Value<Enum::RangeFittingMode::Reinhard>("Reinhard")
			);
		}

		template <>
		void ReflectType<HDRColorCorrectionOperation>()
		{
			Reflect<HDRColorCorrectionOperation, RenderOperation>::Class
			(
				"HDRColorCorrectionOperation",
				{ "GameObject" },

				Member<Bind(&HDRColorCorrectionOperation::LuminescenceType)>("LuminescenceType"),
				Member<Bind(&HDRColorCorrectionOperation::RangeFittingType)>("RangeFittingType"),
				Member<Bind(&HDRColorCorrectionOperation::Exposure)>("Exposure"),
				Member<Bind(&HDRColorCorrectionOperation::BurnoutCutoff)>("BurnoutCutoff"),

				Member<Bind(&HDRColorCorrectionOperation::Input)>("Input"),
				Member<Bind(&HDRColorCorrectionOperation::Output)>("Output"),

				Function(
					"GetLuminescenceBuffer",
					Overload(
						Const,
						Returns<std::shared_ptr<FrameBuffer>>()
					).Bind<HDRColorCorrectionOperation, &HDRColorCorrectionOperation::GetLuminescenceBuffer>()
				),

				Function(
					"Resize",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<int>("width"),
						Argument<int>("height")
					).Bind<HDRColorCorrectionOperation, &HDRColorCorrectionOperation::Resize>()
				)
			);
		}
	}
}