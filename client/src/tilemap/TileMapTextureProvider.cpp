#include "TileMapTextureProvider.hpp"

#include "../level/Level.hpp"

void
TileMapTextureProvider::loadTexture(const FilePath& filePath, ResourceID resourceID, sf::Vector2i tilePosition) {
	internal.loadTexture(filePath, resourceID, sf::IntRect(tilePosition.x, tilePosition.y, TILE_WIDTH, TILE_HEIGHT));
}

const sf::Texture& TileMapTextureProvider::getTexture(ResourceID resourceID) const {
	return internal.getTexture(resourceID);
}
