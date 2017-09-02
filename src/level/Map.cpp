#include "Map.hpp"
#include "../utility/Tokeniser.hpp"

bool Map::checkCollision(const sf::Sprite& sprite) {
	auto x = static_cast<int>(sprite.getPosition().x / TILE_WIDTH);
	auto y = static_cast<int>(sprite.getPosition().y / TILE_HEIGHT);
	if (x < 0 || y < 0) return true;
	return collidableTiles[y][x];
}

void Map::loadMap(const Filepath& filepath) {
	collidableTiles.clear();
	auto details = tokenise<int>(filepath);
	for(auto line : details) {
		std::vector<bool> temp;
		temp.reserve(line.size());
		for(auto tile : line) {
			temp.push_back(tile != 0);
		}
		collidableTiles.push_back(temp);
	}
}
