#include "TileMapTextureProvider.hpp"

#include "Level.hpp"
#include "../resource/ResourceLoaders.hpp"

void TileMapTextureProvider::loadTexture(const FilePath& filePath, ResourceID resourceID, sf::Vector2i tilePosition) {
	internal.storeResource(
			loadTextureFromPath(filePath, sf::IntRect(tilePosition.x, tilePosition.y, TILE_WIDTH, TILE_HEIGHT)), resourceID);
}

const sf::Texture& TileMapTextureProvider::getResource(ResourceID resourceID) const {
	return internal.getResource(resourceID);
}
