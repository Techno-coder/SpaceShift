#include "TestState.hpp"

void TestState::handleEvent(sf::Event& event, sf::RenderTarget& target) {
	switch (event.type) {
		case sf::Event::Resized: {
			sf::View view(sf::FloatRect(posX, posY, event.size.width, event.size.height));
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
	textureProvider.loadTexture("resources/tile_aqua.png", 0);
	tilemap.setTextureProvider(textureProvider);
	tilemap.loadMap("resources/testMap.txt");
}
