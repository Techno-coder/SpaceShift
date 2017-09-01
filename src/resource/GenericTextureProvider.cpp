#include "GenericTextureProvider.hpp"

static sf::Texture emptyTexture;

void SimpleTextureProvider::loadTexture(const Filepath& filePath, ResourceID resourceID) {
	textures[resourceID].loadFromFile(filePath);
}

void SimpleTextureProvider::loadTexture(const Filepath& filePath, ResourceID resourceID, sf::IntRect textureRect) {
	textures[resourceID].loadFromFile(filePath, textureRect);
}

const sf::Texture& SimpleTextureProvider::getTexture(ResourceID resourceID) const {
	if (textures.count(resourceID) == 0) return emptyTexture;
	return textures.at(resourceID);
}
