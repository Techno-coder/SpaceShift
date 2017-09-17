#pragma once

#include "Resource.hpp"

#include <map>
#include <string>

class ResourceIDProvider {
	ResourceID nextID = 0;
	std::map<std::string, ResourceID> resourceIDs;
public:
	ResourceID createNewMapping(const std::string& stringID);
	ResourceID getResourceID(const std::string& stringID) const;
};

