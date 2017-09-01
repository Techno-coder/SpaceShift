#pragma once

#include "../level/Level.hpp"
#include "../resource/Resource.hpp"
#include "../resource/TextureProvider.hpp"
#include "../utility/Filepath.hpp"

#include <SFML/Graphics/Drawable.hpp>

#include <memory>
#include <string>
#include <vector>

class Tilemap : public sf::Drawable {
	std::vector<std::vector<ResourceID>> tiles;
	std::shared_ptr<TextureProvider> provider;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	Tilemap();
	void loadMap(const Filepath& filePath);
	void setTextureProvider(std::shared_ptr<TextureProvider> newProvider);
};

