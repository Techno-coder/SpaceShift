#pragma once

#include "Level.hpp"
#include "../resource/Resource.hpp"
#include "../../../shared/utility/MatrixVector.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <vector>

namespace sf {
	class Sprite;

	class Texture;
}

template <typename T>
class ResourceProvider;

typedef ResourceProvider<sf::Texture> TextureProvider;

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
