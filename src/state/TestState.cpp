#include "TestState.hpp"

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
					player.move(0, -5);
					if(map.checkCollision(player.getSprite())) player.move(0, 5);
					break;
				case sf::Keyboard::S:
					player.move(0, 5);
					if(map.checkCollision(player.getSprite())) player.move(0, -5);
					break;
				case sf::Keyboard::A:
					player.move(-5, 0);
					if(map.checkCollision(player.getSprite())) player.move(5, 0);
					break;
				case sf::Keyboard::D:
					player.move(5, 0);
					if(map.checkCollision(player.getSprite())) player.move(-5, 0);
					break;
				default:
					break;
			}
			posX = player.getSprite().getPosition().x;
			posY = player.getSprite().getPosition().y;
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
	target.draw(player.getSprite());
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
	playerTextureProvider.loadTexture(Filepath("dungeon_tiles.png"), playerTextureIDprovider.createNewMapping("GREEN"),
	                                  sf::IntRect(197, 160, 16, 20));
	tilemap.setTextureProvider(textureProvider);
	tilemap.loadMap(Filepath("testMap.txt"));
	map.loadMap(Filepath("testMap.txt"));
	player.move(20, 20);
	player.setPlayerTexture(playerTextureProvider.getTexture(playerTextureIDprovider.getTextureID("GREEN")));
}
