#pragma once

#include "ResourceProvider.hpp"

#include <memory>
#include <map>

template <typename T>
class GenericResourceProvider : public ResourceProvider<T> {
	std::map<ResourceID, std::unique_ptr<T>> resources;
public:
	void storeResource(std::unique_ptr<T> resource, ResourceID resourceID) {
		resources[resourceID] = std::move(resource);
	};

	const T& getResource(ResourceID resourceID) const override {
		return *resources.at(resourceID);
	};
};

