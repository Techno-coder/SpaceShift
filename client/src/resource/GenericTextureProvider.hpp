#pragma once

#include "Resource.hpp"
#include "TextureProvider.hpp"
#include "../../../shared/utility/FilePath.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <map>

class GenericTextureProvider : public TextureProvider {
	std::map<ResourceID, sf::Texture> textures;
public:
	void loadTexture(const FilePath& filePath, ResourceID resourceID, sf::IntRect textureRect);
	void loadTexture(const FilePath& filePath, ResourceID resourceID);
	const sf::Texture& getTexture(ResourceID resourceID) const override;
};

