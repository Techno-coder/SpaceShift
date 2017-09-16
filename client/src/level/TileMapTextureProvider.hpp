#pragma once

#include "../resource/Resource.hpp"
#include "../resource/GenericTextureProvider.hpp"
#include "../../../shared/utility/FilePath.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <string>

class TileMapTextureProvider : public TextureProvider {
	GenericTextureProvider internal;
public:
	void loadTexture(const FilePath& filePath, ResourceID resourceID, sf::Vector2i tilePosition);
	const sf::Texture& getTexture(ResourceID resourceID) const override;
};

