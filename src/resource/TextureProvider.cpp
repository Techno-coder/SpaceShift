#include "TextureProvider.hpp"

static TextureProvider emptyProvider;

const sf::Texture& TextureProvider::getTexture(ResourceID resourceID) const {
	return textures.at(resourceID);
}

TextureProvider& TextureProvider::empty() {
	return emptyProvider;
}

void TextureProvider::loadTexture(const std::string& filePath, ResourceID resourceID) {
	textures[resourceID].loadFromFile(filePath);
}
