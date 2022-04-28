#pragma once

#include <string>
#include <map>

#include "Vector3.h"
#include "Object.h"

namespace GraphicsEngine
{
	class Texture;

	class Font : public Engine::Object
	{
	public:
		class Character
		{
		public:
			char Value = 0;
			Float AspectRatio = 1;
			Float KerningLeft = 0;
			Float KerningRight = 0;
			Float VerticalOffset = 0;
			Vector3 TextOffset;
			Vector3 TextScale;

			Character();
			Character(char character, Float aspectRatio, const Vector3& textOffset, const Vector3& textScale, Float kerningLeft, Float kerningRight, Float verticalOffset);
		};

		Float SpaceWidth = 0.3f;
		int TabSpaces = 4;

		void Load(const std::string& filePath, const std::string& textureName);
		const Character& GetCharacter(char character) const;
		std::shared_ptr<Texture> GetTexture() const;

	private:
		typedef std::map< char, Character > CharacterMap;

		CharacterMap Characters;
		std::weak_ptr<Texture> Glyphs;

		Character Nope = Character(0, 1, Vector3(), Vector3(), 0, 0, 0);
	};
}