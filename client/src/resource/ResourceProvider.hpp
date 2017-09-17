#pragma once

#include "Resource.hpp"

#include <SFML/Graphics/Texture.hpp>

template <typename T>
class ResourceProvider {
public:
	virtual const T& getResource(ResourceID resourceID) const = 0;
};

typedef ResourceProvider<sf::Texture> TextureProvider;
