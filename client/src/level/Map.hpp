#pragma once

#include "Level.hpp"
#include "../resource/Resource.hpp"
#include <utility/MatrixVector.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <vector>

namespace sf {
	class Sprite;

	class Texture;
}

template <typename T> class ResourceProvider;
template <typename T> class ResourceIDProvider;

typedef ResourceProvider<sf::Texture> TextureProvider;

class Map : public sf::Drawable {
	MatrixVector<bool> collisionTiles;
	MatrixVector<ResourceID> tiles;
	TextureProvider& textureProvider;
	ResourceIDProvider<ResourceID>& resourceIDProvider;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	Map(ResourceIDProvider<ResourceID>& resourceIDProvider, TextureProvider& textureProvider);

	/**
	 * Checks whether a sprite is colliding with the tiles
	 * @param sprite The sprite to check
	 * @return True if the sprite is colliding with the tiles
	 */
	bool checkCollision(const sf::Sprite& sprite);
	void loadMap(MatrixVector<ResourceID> newMap);
};
