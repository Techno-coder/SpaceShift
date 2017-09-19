#pragma once

#include "Resource.hpp"

#include <map>
#include <string>

template <typename K>
class ResourceIDProvider {
	ResourceID nextID = 0;
	std::map<K, ResourceID> resourceIDs;
public:
	/**
	 * Sets the nextID value (inclusive)
	 * This means the next mapping created will return this value
	 * @param newOffset The value nextID will be set to
	 */
	void setIDOffset(ResourceID newOffset) {
		nextID = newOffset;
	}

	ResourceID createNewMapping(const K& ID) {
		resourceIDs[ID] = nextID++;
		return resourceIDs[ID];
	}

	ResourceID getResourceID(const K& ID) const {
		return resourceIDs.at(ID);
	}
};

