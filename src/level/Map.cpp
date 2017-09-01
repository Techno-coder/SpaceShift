#include "Map.hpp"

bool Map::checkCollision(const sf::Sprite& sprite) {
	auto x = static_cast<int>(sprite.getPosition().x / TILE_WIDTH);
	auto y = static_cast<int>(sprite.getPosition().y / TILE_HEIGHT);
	return collidableTiles[y][x];
}
