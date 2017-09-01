#include "Tilemap.hpp"
#include "../resource/GenericTextureProvider.hpp"
#include "../utility/Tokeniser.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

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

void Tilemap::loadMap(const Filepath& filePath) {
	tiles.clear();
	tiles = tokenise<ResourceID>(filePath);
}

void Tilemap::setTextureProvider(std::shared_ptr<TextureProvider> newProvider) {
	provider = std::move(newProvider);
}

Tilemap::Tilemap() : provider(std::make_shared<SimpleTextureProvider>()) {}
