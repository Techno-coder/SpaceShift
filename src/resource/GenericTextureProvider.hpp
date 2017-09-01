#pragma once

#include "Resource.hpp"
#include "TextureProvider.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <map>

class SimpleTextureProvider : public TextureProvider {
	std::map<ResourceID, sf::Texture> textures;
public:
	void loadTexture(const std::string& filePath, ResourceID resourceID, sf::IntRect textureRect);
	void loadTexture(const std::string& filePath, ResourceID resourceID);
	const sf::Texture& getTexture(ResourceID resourceID) const override;

	/**
	 * Get an empty texture provider
	 * Note that textures can be set and retrieved from this static provider but it is not recommended
	 * @return An empty texture provider
	 */
	static SimpleTextureProvider& empty();
};

