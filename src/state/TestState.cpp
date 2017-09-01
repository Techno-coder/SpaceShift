#include "TestState.hpp"
#include "../utility/Filepath.hpp"

void TestState::handleEvent(sf::Event& event, sf::RenderTarget& target) {
	switch (event.type) {
		case sf::Event::Resized: {
			sf::View view(sf::FloatRect(posX, posY, event.size.width, event.size.height));
			view.zoom(0.2);
			view.setCenter(posX, posY);
			target.setView(view);
			break;
		}
		case sf::Event::KeyPressed: {
			switch (event.key.code) {
				case sf::Keyboard::W:
					posY -= 5;
					break;
				case sf::Keyboard::S:
					posY += 5;
					break;
				case sf::Keyboard::A:
					posX -= 5;
					break;
				case sf::Keyboard::D:
					posX += 5;
					break;
				default:
					break;
			}
			sf::View view(sf::FloatRect(posX, posY, target.getSize().x, target.getSize().y));
			view.setCenter(posX, posY);
			view.zoom(0.2);
			target.setView(view);
		}
		default:
			break;
	}
}

void TestState::update() {

}

void TestState::draw(sf::RenderTarget& target) {
	target.draw(tilemap);
}

void TestState::onEnter() {
	textureProvider->loadTexture(Filepath("dungeon_tiles.png"), 0, sf::Vector2i(48, 48));
	textureProvider->loadTexture(Filepath("dungeon_tiles.png"), 1, sf::Vector2i(32, 32));
	textureProvider->loadTexture(Filepath("dungeon_tiles.png"), 2, sf::Vector2i(48, 32));
	textureProvider->loadTexture(Filepath("dungeon_tiles.png"), 3, sf::Vector2i(96, 32));
	textureProvider->loadTexture(Filepath("dungeon_tiles.png"), 4, sf::Vector2i(96, 48));
	textureProvider->loadTexture(Filepath("dungeon_tiles.png"), 5, sf::Vector2i(96, 96));
	textureProvider->loadTexture(Filepath("dungeon_tiles.png"), 6, sf::Vector2i(64, 96));
	textureProvider->loadTexture(Filepath("dungeon_tiles.png"), 7, sf::Vector2i(32, 96));
	textureProvider->loadTexture(Filepath("dungeon_tiles.png"), 8, sf::Vector2i(32, 64));
	tilemap.setTextureProvider(textureProvider);
	tilemap.loadMap(Filepath("testMap.txt"));
}
