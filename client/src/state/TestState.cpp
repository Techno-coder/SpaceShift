#include "TestState.hpp"

void TestState::handleEvent(sf::Event& event, sf::RenderTarget& target) {
	switch (event.type) {
		default:
			break;
	}
}

void TestState::update() {
	handleKeyboardInput();
}

void TestState::draw(sf::RenderTarget& target) {
	sf::View view(sf::FloatRect(posX, posY, target.getSize().x, target.getSize().y));
	view.setCenter(posX, posY);
	view.zoom(0.2);
	target.setView(view);

	target.draw(tileMap);
	target.draw(player.getSprite());
}

void TestState::onEnter() {
	textureProvider->loadTexture(FilePath("dungeon_tiles.png"), 0, sf::Vector2i(48, 48));
	textureProvider->loadTexture(FilePath("dungeon_tiles.png"), 1, sf::Vector2i(32, 32));
	textureProvider->loadTexture(FilePath("dungeon_tiles.png"), 2, sf::Vector2i(48, 32));
	textureProvider->loadTexture(FilePath("dungeon_tiles.png"), 3, sf::Vector2i(96, 32));
	textureProvider->loadTexture(FilePath("dungeon_tiles.png"), 4, sf::Vector2i(96, 48));
	textureProvider->loadTexture(FilePath("dungeon_tiles.png"), 5, sf::Vector2i(96, 96));
	textureProvider->loadTexture(FilePath("dungeon_tiles.png"), 6, sf::Vector2i(64, 96));
	textureProvider->loadTexture(FilePath("dungeon_tiles.png"), 7, sf::Vector2i(32, 96));
	textureProvider->loadTexture(FilePath("dungeon_tiles.png"), 8, sf::Vector2i(32, 64));
	playerTextureProvider.loadTexture(FilePath("dungeon_tiles.png"), playerTextureIDProvider.createNewMapping("GREEN"),
	                                  sf::IntRect(197, 160, 16, 20));
	tileMap.setTextureProvider(textureProvider);
	tileMap.loadMap(FilePath("testMap.txt"));
	map.loadMap(FilePath("testMap.txt"));
	player.move(20, 20);
	player.setPlayerTexture(playerTextureProvider.getTexture(playerTextureIDProvider.getTextureID("GREEN")));
}

void TestState::handleKeyboardInput() {
	constexpr int moveSpeed = 3;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player.move(0, -moveSpeed);
		if (map.checkCollision(player.getSprite())) player.move(0, moveSpeed);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player.move(0, moveSpeed);
		if (map.checkCollision(player.getSprite())) player.move(0, -moveSpeed);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player.move(-moveSpeed, 0);
		if (map.checkCollision(player.getSprite())) player.move(moveSpeed, 0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player.move(moveSpeed, 0);
		if (map.checkCollision(player.getSprite())) player.move(-moveSpeed, 0);
	}
	posX = player.getSprite().getPosition().x;
	posY = player.getSprite().getPosition().y;
}
