#include "Player.hpp"

#include <SFML/Graphics/Texture.hpp>

void Player::move(int xOffset, int yOffset) {
	sprite.move(xOffset, yOffset);
}

void Player::setPlayerTexture(const sf::Texture& texture) {
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

sf::Sprite& Player::getSprite() {
	return sprite;
}
