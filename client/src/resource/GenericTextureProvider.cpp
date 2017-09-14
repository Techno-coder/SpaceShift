#include "GenericTextureProvider.hpp"

static sf::Texture emptyTexture;

void GenericTextureProvider::loadTexture(const FilePath& filePath, ResourceID resourceID) {
	textures[resourceID].loadFromFile(filePath);
}

void GenericTextureProvider::loadTexture(const FilePath& filePath, ResourceID resourceID, sf::IntRect textureRect) {
	textures[resourceID].loadFromFile(filePath, textureRect);
}

const sf::Texture& GenericTextureProvider::getTexture(ResourceID resourceID) const {
	if (textures.count(resourceID) == 0) return emptyTexture;
	return textures.at(resourceID);
}
