#pragma once

#include "Level.hpp"
#include "../utility/Filepath.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <vector>

class Map {
	std::vector<std::vector<bool>> collidableTiles;
public:
	/**
	 * Checks whether a sprite is colliding with the tiles
	 * @param sprite The sprite to check
	 * @return True if the sprite is colliding with the tiles
	 */
	bool checkCollision(const sf::Sprite& sprite);

	void loadMap(const Filepath& filepath);
};
