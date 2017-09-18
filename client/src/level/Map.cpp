#include "Map.hpp"
#include "../resource/ResourceIDProvider.hpp"
#include "../resource/GenericResourceProvider.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

bool Map::checkCollision(const sf::Sprite& sprite) {
	auto x = static_cast<int>(sprite.getPosition().x / TILE_WIDTH);
	auto y = static_cast<int>(sprite.getPosition().y / TILE_HEIGHT);
	if (x < 0 || y < 0) return true;
	return collisionTiles[y][x];
}

void Map::loadMap(MatrixVector<ResourceID> newMap) {
	collisionTiles.clear();
	tiles.clear();
	tiles = std::move(newMap);

	for (const auto& line : tiles) {
		std::vector<bool> temp;
		temp.reserve(line.size());
		for (auto tile : line) {
			temp.push_back(tile != 0);
		}
		collisionTiles.push_back(temp);
	}
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	int currentX = 0, currentY = 0;
	for (const auto& row : tiles) {
		for (const auto& tile : row) {
			sf::Sprite tileSprite;
			tileSprite.setTexture(textureProvider.getResource(resourceIDProvider.getResourceID(tile)));
			tileSprite.setPosition(currentX, currentY);
			target.draw(tileSprite);
			currentX += TILE_WIDTH;
		}
		currentX = 0;
		currentY += TILE_HEIGHT;
	}
}

Map::Map(ResourceIDProvider<ResourceID>& resourceIDProvider, TextureProvider& textureProvider)
		: resourceIDProvider(resourceIDProvider), textureProvider(textureProvider) {

}
