#pragma once

#include "Resource.hpp"

#include <SFML/Graphics/Texture.hpp>

class TextureProvider {
public:
	virtual const sf::Texture& getTexture(ResourceID resourceID) const = 0;
};