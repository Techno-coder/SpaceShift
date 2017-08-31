#include "Tilemap.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <fstream>
#include <sstream>

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	int currentX = 0, currentY = 0;
	for (const auto& row : tiles) {
		sf::Vector2u lastTextureSize;
		for (const auto& tile : row) {
			sf::Sprite tileSprite;
			tileSprite.setTexture(provider.getTexture(tile));
			tileSprite.setPosition(currentX, currentY);
			target.draw(tileSprite);
			lastTextureSize = tileSprite.getTexture()->getSize();
			currentX += lastTextureSize.x;
		}
		currentX = 0;
		currentY += lastTextureSize.y;
	}
}

void Tilemap::loadMap(const std::string& filePath) {
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

void Tilemap::setTextureProvider(const TextureProvider& newProvider) {
	provider = newProvider;
}

Tilemap::Tilemap() : provider(TextureProvider::empty()) {}
