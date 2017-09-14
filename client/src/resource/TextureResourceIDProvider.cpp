#include "TextureResourceIDProvider.hpp"

ResourceID TextureResourceIDProvider::createNewMapping(const std::string& stringID) {
	texturesIDs[stringID] = nextID++;
	return texturesIDs[stringID];
}

ResourceID TextureResourceIDProvider::getTextureID(const std::string& stringID) const {
	return texturesIDs.at(stringID);
}
