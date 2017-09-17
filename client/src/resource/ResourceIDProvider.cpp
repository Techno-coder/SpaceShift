#include "ResourceIDProvider.hpp"

ResourceID ResourceIDProvider::createNewMapping(const std::string& stringID) {
	resourceIDs[stringID] = nextID++;
	return resourceIDs[stringID];
}

ResourceID ResourceIDProvider::getResourceID(const std::string& stringID) const {
	return resourceIDs.at(stringID);
}
