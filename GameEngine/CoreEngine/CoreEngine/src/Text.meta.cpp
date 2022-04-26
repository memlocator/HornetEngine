#include "Text.h"

#include "Font.h"
#include "FrameBuffer.h"
#include "Texture.h"
#include "Appearance.h"
#include "ScreenCanvas.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Text>()
		{
			Reflect<Text, Object>::Class
			(
				"Text",
				{ "GameObject" },

				Member<Bind(&Text::TextColor)>("TextColor"),
				Member<Bind(&Text::WrapText)>("WrapText"),
				Member<Bind(&Text::LineSpacing)>("LineSpacing"),
				Member<Bind(&Text::FontSize)>("FontSize"),
				Member<Bind(&Text::FontData)>("FontData"),

				Property(
					"Contents",
					Getter<std::string>(Const).Bind<Text, &Text::GetText>(),
					Setter<const std::string&>(Mutable).Bind<Text, &Text::SetText>()
				),

				Constructor(
					Overload()
				),

				Function(
					"Draw",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::shared_ptr<GraphicsEngine::FrameBuffer>&>("output")
					).Bind<Text, &Text::Draw>()
				),

				Function(
					"SetText",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("text")
					).Bind<Text, &Text::SetText>()
				),

				Function(
					"GetText",
					Overload(
						Const,
						Returns<std::string>()
					).Bind<Text, &Text::GetText>()
				),

				Function(
					"GetTexture",
					Overload(
						Const,
						Returns<const std::shared_ptr<Texture>&>()
					).Bind<Text, &Text::GetTexture>()
				),

				Function(
					"GetBuffer",
					Overload(
						Const,
						Returns<const std::shared_ptr<FrameBuffer>&>()
					).Bind<Text, &Text::GetBuffer>()
				),

				Function(
					"GetAppearance",
					Overload(
						Const,
						Returns<const std::shared_ptr<Appearance>&>()
					).Bind<Text, &Text::GetAppearance>()
				),

				Function(
					"Create",
					Overload(
						Static,
						Returns<std::shared_ptr<Text>>(),
						Argument<const std::shared_ptr<Font>&>("font"),
						Argument<const std::shared_ptr<ScreenCanvas>&>("parent"),
						Argument<const std::string&>("name"),
						Argument<const std::string&>("text")
					).Bind<&Text::Create>()
				)
			);
		}
	}
}