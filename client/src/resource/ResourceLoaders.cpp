#include "ResourceLoaders.hpp"

#include "../../../shared/utility/FilePath.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

std::unique_ptr<sf::Texture> loadTextureFromPath(const FilePath& filePath) {
	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
	texture->loadFromFile(filePath);
	return texture;
}

std::unique_ptr<sf::Texture> loadTextureFromPath(const FilePath& filePath, sf::IntRect textureRect) {
	std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();
	texture->loadFromFile(filePath, textureRect);
	return texture;
}

std::unique_ptr<sf::SoundBuffer> loadSoundFromPath(const FilePath& filePath) {
	std::unique_ptr<sf::SoundBuffer> sound = std::make_unique<sf::SoundBuffer>();
	sound->loadFromFile(filePath);
	return sound;
}
