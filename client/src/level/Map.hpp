#pragma once

#include "Level.hpp"
#include "../utility/FilePath.hpp"
#include "../utility/Tokenizer.hpp"
#include "../resource/TextureProvider.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include <vector>

class Map : public sf::Drawable {
	MatrixVector<bool> collisionTiles;
	MatrixVector<ResourceID> tiles;
	std::shared_ptr<TextureProvider> provider;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	Map();

	/**
	 * Checks whether a sprite is colliding with the tiles
	 * @param sprite The sprite to check
	 * @return True if the sprite is colliding with the tiles
	 */
	bool checkCollision(const sf::Sprite& sprite);

	void loadMap(MatrixVector<ResourceID> newMap);
	void setTextureProvider(std::shared_ptr<TextureProvider> newProvider);
};
