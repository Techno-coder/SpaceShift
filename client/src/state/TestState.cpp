#include "TestState.hpp"
#include "../../../shared/packets/server/MapChangeEvent.hpp"
#include "../../../shared/packets/client/PlayerMoveRequest.hpp"

void TestState::handleEvent(sf::Event& event, sf::RenderTarget& target) {
	switch (event.type) {
		case sf::Event::Closed:
			networkClient.closeConnection();
			break;
		case sf::Event::KeyPressed:
			break;
		default:
			break;
	}
}

void TestState::update() {
	handleKeyboardInput();
	if (networkClient.receiveNewPacket()) {
		ServerPacketWrapper newPacket = networkClient.getRecentPacket();
		if (newPacket.type == ServerPacketWrapper::Type::MAP_CHANGE_EVENT) {
			printf("MAP_CHANGE_EVENT packet received\n");
			MapChangeEventPacket mapChangeEventPacket;
			mapChangeEventPacket.parsePacket(newPacket.internal);
			map.loadMap(tokenize<ResourceID>(mapChangeEventPacket.serializedMapData));
		}
	}
	currentTime += networkClock.restart();
	if (currentTime > sf::milliseconds(100)) {
		printf("Move request packet sent\n");
		PlayerMoveRequestPacket moveRequestPacket;
		moveRequestPacket.newPositionX = static_cast<int>(posX);
		moveRequestPacket.newPositionY = static_cast<int>(posY);
		networkClient.sendPacket(moveRequestPacket);
		currentTime = sf::Time::Zero;
	}
}

void TestState::draw(sf::RenderTarget& target) {
	sf::View view(sf::FloatRect(posX, posY, target.getSize().x, target.getSize().y));
	view.setCenter(posX, posY);
	view.zoom(0.2);
	target.setView(view);

	target.draw(map);
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
	map.setTextureProvider(textureProvider);
	map.loadMap(tokenize<ResourceID>(FilePath("testMap.txt")));
	player.move(20, 20);
	player.setPlayerTexture(playerTextureProvider.getTexture(playerTextureIDProvider.getTextureID("GREEN")));

//	networkClient.openConnection("104.236.159.163", 54000);
	if (networkClient.openConnection(sf::IpAddress::LocalHost, 54000))
		printf("Connection successful\n"); //TODO Change to server address
	else printf("Unable to connect");
}

void TestState::handleKeyboardInput() {
	constexpr int moveSpeed = 3;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		player.move(0, -moveSpeed);
		if (map.checkCollision(player.getSprite())) player.move(0, moveSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		player.move(0, moveSpeed);
		if (map.checkCollision(player.getSprite())) player.move(0, -moveSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player.move(-moveSpeed, 0);
		if (map.checkCollision(player.getSprite())) player.move(moveSpeed, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		player.move(moveSpeed, 0);
		if (map.checkCollision(player.getSprite())) player.move(-moveSpeed, 0);
	}
	posX = player.getSprite().getPosition().x;
	posY = player.getSprite().getPosition().y;
}
