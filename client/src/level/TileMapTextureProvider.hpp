#pragma once

#include "../resource/Resource.hpp"
#include "../resource/GenericResourceProvider.hpp"
#include "../../../shared/utility/FilePath.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <string>

class TileMapTextureProvider : public ResourceProvider<sf::Texture> {
	GenericResourceProvider<sf::Texture> internal;
public:
	void loadTexture(const FilePath& filePath, ResourceID resourceID, sf::Vector2i tilePosition);
	const sf::Texture& getResource(ResourceID resourceID) const override;
};

