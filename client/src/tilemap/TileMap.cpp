#include "TileMap.hpp"
#include "../resource/GenericTextureProvider.hpp"
#include "../utility/Tokeniser.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
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

void TileMap::loadMap(const FilePath& filePath) {
	tiles.clear();
	tiles = tokenize<ResourceID>(filePath);
}

void TileMap::setTextureProvider(std::shared_ptr<TextureProvider> newProvider) {
	provider = std::move(newProvider);
}

TileMap::TileMap() : provider(std::make_shared<GenericTextureProvider>()) {}
