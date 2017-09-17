#pragma once

#include "../../../shared/utility/FilePath.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

std::unique_ptr<sf::Texture> loadTextureFromPath(const FilePath& filePath);
std::unique_ptr<sf::Texture> loadTextureFromPath(const FilePath& filePath, sf::IntRect textureRect);

std::unique_ptr<sf::SoundBuffer> loadSoundFromPath(const FilePath& filePath);
