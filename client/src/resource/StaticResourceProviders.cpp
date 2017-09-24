#include "StaticResourceProviders.hpp"
#include "ResourceLoaders.hpp"
#include "../level/Level.hpp"
#include <utility/FilePath.hpp>

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <thread>

GenericResourceProvider<sf::Texture> globalTextures;
ResourceIDProvider<ResourceID> globalTileMapTextureIDs; //TODO consider having a tile map ID provider

GenericResourceProvider<sf::SoundBuffer> globalSounds;
ResourceIDProvider<std::string> globalSoundIDs;

GenericResourceProvider<sf::Font> globalFonts;
ResourceIDProvider<GlobalFont> globalFontIDs;

ResourceID loadTile(int positionX, int positionY, ResourceID tileID) {
	const FilePath tileMapPath("dungeon_tiles.png");
	const sf::Vector2i tileSize(TILE_WIDTH, TILE_HEIGHT);
	const ResourceID mapping = globalTileMapTextureIDs.createNewMapping(tileID);
	globalTextures.storeResource(loadTileFromPath(tileMapPath, {positionX, positionY}, tileSize), mapping);
	return mapping;
}

ResourceID loadDefaultTileMap() {
	loadTile(48, 48, 0);
	loadTile(32, 32, 1);
	loadTile(48, 32, 2);
	loadTile(96, 32, 3);
	loadTile(96, 48, 4);
	loadTile(96, 96, 5);
	loadTile(64, 96, 6);
	loadTile(32, 96, 7);
	return loadTile(32, 64, 8);
}

void loadTextures() {
	loadDefaultTileMap();
	// TODO when doing the next textures make sure to set offset of the resource ID providers
}

void loadSounds() {
	//TODO
}

void loadFont(const std::string& fontFileName, const GlobalFont& fontID) {
	const std::string fontsPrefix = "fonts/";
	globalFonts.storeResource(loadFontFromPath(FilePath(fontsPrefix + fontFileName)),
	                          globalFontIDs.createNewMapping(fontID));
}

void loadFonts() {
	loadFont("kenvector_future.ttf", GlobalFont::KENVECTOR);
	loadFont("kenvector_future_thin.ttf", GlobalFont::KENVECTOR_THIN);
	//TODO REST
}

void loadAllDefaultResources() {
	std::thread sounds(loadSounds);
	std::thread fonts(loadFonts);
	loadTextures();
	sounds.join();
	fonts.join();
}
