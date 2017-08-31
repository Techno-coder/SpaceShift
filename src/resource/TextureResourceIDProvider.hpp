#pragma once

#include "Resource.hpp"

#include <map>
#include <string>

class TextureResourceIDProvider {
	std::map<std::string, ResourceID> texturesIDs;
public:
	void setMapping(std::string stringID, ResourceID resourceID);
	ResourceID getTextureID(std::string stringID);
};

