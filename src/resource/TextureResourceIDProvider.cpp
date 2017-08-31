#include "TextureResourceIDProvider.hpp"

void TextureResourceIDProvider::setMapping(std::string stringID, ResourceID resourceID) {
	texturesIDs[stringID] = resourceID;
}

ResourceID TextureResourceIDProvider::getTextureID(std::string stringID) {
	return texturesIDs[stringID];
}
