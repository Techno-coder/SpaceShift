#pragma once

#include "Resource.hpp"
#include "TextureProvider.hpp"
#include "../utility/Filepath.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <map>

class SimpleTextureProvider : public TextureProvider {
	std::map<ResourceID, sf::Texture> textures;
public:
	void loadTexture(const Filepath& filePath, ResourceID resourceID, sf::IntRect textureRect);
	void loadTexture(const Filepath& filePath, ResourceID resourceID);
	const sf::Texture& getTexture(ResourceID resourceID) const override;
};

