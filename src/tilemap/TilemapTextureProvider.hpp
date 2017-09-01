#pragma once

#include "../resource/Resource.hpp"
#include "../resource/GenericTextureProvider.hpp"
#include "../utility/Filepath.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <string>

class TilemapTextureProvider : public TextureProvider {
	SimpleTextureProvider internal;
public:
	void loadTexture(const Filepath& filePath, ResourceID resourceID, sf::Vector2i tilePosition);
	const sf::Texture& getTexture(ResourceID resourceID) const override;
};

