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

extern GenericResourceProvider<sf::Font> globalFonts;
extern ResourceIDProvider<std::string> globalFontIDs;

void loadAllDefaultResources();
