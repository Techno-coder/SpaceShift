#pragma once

#include <SFML/Graphics/Rect.hpp>

namespace sf {
	class Texture;

	class SoundBuffer;

	class Font;
}

class FilePath;

std::unique_ptr<sf::Texture> loadTextureFromPath(const FilePath& filePath);
std::unique_ptr<sf::Texture> loadTextureFromPath(const FilePath& filePath, sf::IntRect textureRect);
std::unique_ptr<sf::Texture>
loadTileFromPath(const FilePath& filePath, sf::Vector2i texturePosition, sf::Vector2i tileSize);

std::unique_ptr<sf::SoundBuffer> loadSoundFromPath(const FilePath& filePath);

std::unique_ptr<sf::Font> loadFontFromPath(const FilePath& filePath);
