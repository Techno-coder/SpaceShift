#include "Tilemap.hpp"
#include "../resource/GenericTextureProvider.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <fstream>
#include <sstream>

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	int currentX = 0, currentY = 0;
	for (const auto& row : tiles) {
		for (const auto& tile : row) {
			sf::Sprite tileSprite;
			tileSprite.setTexture(provider->getTexture(tile));
			tileSprite.setPosition(currentX, currentY);
			target.draw(tileSprite);
			currentX += TILE_WIDTH;
		}
		currentX = 0;
		currentY += TILE_HEIGHT;
	}
}

void Tilemap::loadMap(const std::string& filePath) {
	tiles.clear();
	std::ifstream in(filePath);
	if (!in.good()) return;
	std::string lineString;
	while (std::getline(in, lineString)) {
		std::istringstream line(lineString);
		std::vector<ResourceID> lineTokens;
		ResourceID tile;
		while (line >> tile) {
			lineTokens.emplace_back(tile);
		}
		tiles.push_back(lineTokens);
	}
}

void Tilemap::setTextureProvider(std::shared_ptr<TextureProvider> newProvider) {
	provider = std::move(newProvider);
}

Tilemap::Tilemap() : provider(std::make_shared<SimpleTextureProvider>()) {}
