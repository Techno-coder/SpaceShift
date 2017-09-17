#pragma once

#include "Resource.hpp"

template <typename T>
class ResourceProvider {
public:
	virtual const T& getResource(ResourceID resourceID) const = 0;
};

namespace sf {
	class Texture;
}

typedef ResourceProvider<sf::Texture> TextureProvider;
