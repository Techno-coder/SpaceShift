#pragma once

#include "../resource/Resource.hpp"
#include "../resource/GenericTextureProvider.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <string>

class TilemapTextureProvider : public TextureProvider {
	SimpleTextureProvider internal;
public:
	void loadTexture(const std::string& filePath, ResourceID resourceID, sf::Vector2i tilePosition);
	const sf::Texture& getTexture(ResourceID resourceID) const override;
};

