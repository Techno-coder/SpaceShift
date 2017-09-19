#pragma once

#include "GenericResourceProvider.hpp"
#include "ResourceIDProvider.hpp"

namespace sf {
	class SoundBuffer;

	class Font;
}

extern GenericResourceProvider<sf::Texture> globalTextures;
extern ResourceIDProvider<ResourceID> globalTileMapTextureIDs;

extern GenericResourceProvider<sf::SoundBuffer> globalSounds;
extern ResourceIDProvider<std::string> globalSoundIDs;

enum class GlobalFont {
	KENVECTOR,
	KENVECTOR_THIN
};
extern GenericResourceProvider<sf::Font> globalFonts;
extern ResourceIDProvider<GlobalFont> globalFontIDs;

void loadAllDefaultResources();
