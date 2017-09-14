#pragma once

#include "Resource.hpp"

#include <map>
#include <string>

class TextureResourceIDProvider {
	ResourceID nextID = 0;
	std::map<std::string, ResourceID> texturesIDs;
public:
	ResourceID createNewMapping(const std::string& stringID);
	ResourceID getTextureID(const std::string& stringID) const;
};

