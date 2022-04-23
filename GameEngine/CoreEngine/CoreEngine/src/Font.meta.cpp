#include "Font.h"

#include "Texture.h"

#include "Reflection/Reflection.h"

namespace Engine
{
	namespace Reflection
	{
		using namespace GraphicsEngine;

		template <>
		void ReflectType<Font>()
		{
			Reflect<Font, Object>::Class
			(
				"Font",
				{ "GameObject" },

				Member<Bind(&Font::SpaceWidth)>("SpaceWidth"),
				Member<Bind(&Font::TabSpaces)>("TabSpaces"),

				Function(
					"Load",
					Overload(
						Mutable,
						Returns<void>(),
						Argument<const std::string&>("filePath"),
						Argument<const std::string&>("textureName")
					).Bind<Font, &Font::Load>()
				),

				Function(
					"GetCharacter",
					Overload(
						Const,
						Returns<const Font::Character&>(),
						Argument<char>("character")
					).Bind<Font, &Font::GetCharacter>()
				),

				Function(
					"GetTexture",
					Overload(
						Const,
						Returns<std::shared_ptr<Texture>>()
					).Bind<Font, &Font::GetTexture>()
				)
			);
		}

		template <>
		void ReflectType<Font::Character>()
		{
			Reflect<Font::Character>::Type
			(
				"Character",

				Member<Bind(&Font::Character::Value)>("Value"),
				Member<Bind(&Font::Character::AspectRatio)>("AspectRatio"),
				Member<Bind(&Font::Character::KerningLeft)>("KerningLeft"),
				Member<Bind(&Font::Character::KerningRight)>("KerningRight"),
				Member<Bind(&Font::Character::VerticalOffset)>("VerticalOffset"),
				Member<Bind(&Font::Character::TextOffset)>("TextOffset"),
				Member<Bind(&Font::Character::TextScale)>("TextScale"),

				Constructor(
					Overload(),
					Overload(
						Argument<char>("character"),
						Argument<float>("aspectRatio"),
						Argument<const Vector3&>("textOffset"),
						Argument<const Vector3&>("textScale"),
						Argument<float>("kerningLeft"),
						Argument<float>("kerningRight"),
						Argument<float>("verticalOffset")
					)
				)
			);
		}
	}
}