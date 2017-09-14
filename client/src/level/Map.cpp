#include "Map.hpp"

bool Map::checkCollision(const sf::Sprite& sprite) {
	auto x = static_cast<int>(sprite.getPosition().x / TILE_WIDTH);
	auto y = static_cast<int>(sprite.getPosition().y / TILE_HEIGHT);
	if (x < 0 || y < 0) return true;
	return collisionTiles[y][x];
}

void Map::loadMap(const FilePath& filePath) {
	collisionTiles.clear();
	auto details = tokenize<int>(filePath);
	for (auto line : details) {
		std::vector<bool> temp;
		temp.reserve(line.size());
		for (auto tile : line) {
			temp.push_back(tile != 0);
		}
		collisionTiles.push_back(temp);
	}
}
