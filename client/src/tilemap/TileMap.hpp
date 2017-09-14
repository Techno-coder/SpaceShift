#pragma once

#include "../level/Level.hpp"
#include "../resource/Resource.hpp"
#include "../resource/TextureProvider.hpp"
#include "../utility/FilePath.hpp"
#include "../utility/Tokeniser.hpp"

#include <SFML/Graphics/Drawable.hpp>

#include <memory>
#include <string>
#include <vector>

class TileMap : public sf::Drawable {
	MatrixVector<ResourceID> tiles;
	std::shared_ptr<TextureProvider> provider;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	TileMap();
	void loadMap(const FilePath& filePath);
	void setTextureProvider(std::shared_ptr<TextureProvider> newProvider);
};

