#pragma once

#include "resource/Resource.hpp"
#include "resource/TextureProvider.hpp"

#include <SFML/Graphics/Drawable.hpp>

#include <string>
#include <vector>

class Tilemap : public sf::Drawable {
	std::vector<std::vector<ResourceID>> tiles;
	TextureProvider& provider;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	Tilemap();
	void loadMap(const std::string& filePath);
	void setTextureProvider(const TextureProvider& newProvider);
};

