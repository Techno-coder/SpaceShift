#pragma once

#include "Level.hpp"
#include "../utility/FilePath.hpp"
#include "../utility/Tokeniser.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <vector>

class Map {
	MatrixVector<bool> collisionTiles;
public:
	/**
	 * Checks whether a sprite is colliding with the tiles
	 * @param sprite The sprite to check
	 * @return True if the sprite is colliding with the tiles
	 */
	bool checkCollision(const sf::Sprite& sprite);

	void loadMap(const FilePath& filePath);
};
