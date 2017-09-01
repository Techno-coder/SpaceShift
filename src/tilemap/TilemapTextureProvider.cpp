#include "TilemapTextureProvider.hpp"

#include "../level/Level.hpp"

void
TilemapTextureProvider::loadTexture(const Filepath& filePath, ResourceID resourceID, sf::Vector2i tilePosition) {
	internal.loadTexture(filePath, resourceID, sf::IntRect(tilePosition.x, tilePosition.y, TILE_WIDTH, TILE_HEIGHT));
}

const sf::Texture& TilemapTextureProvider::getTexture(ResourceID resourceID) const {
	return internal.getTexture(resourceID);
}
