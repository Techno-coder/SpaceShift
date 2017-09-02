#pragma once

#include <SFML/Graphics/Sprite.hpp>

class Player {
	sf::Sprite sprite;
public:
	void setPlayerTexture(const sf::Texture& texture);
	void move(int xOffset, int yOffset);

	sf::Sprite& getSprite();
};

