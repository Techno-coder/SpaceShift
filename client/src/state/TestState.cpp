#include "TestState.hpp"
#include "../resource/ResourceLoaders.hpp"

#include <packets/server/MapChangeEvent.hpp>
#include <packets/client/PlayerMoveRequest.hpp>
#include <utility/Tokenizer.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

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
//		printf("Move request packet sent\n");
//		PlayerMoveRequestPacket moveRequestPacket;
//		moveRequestPacket.newPositionX = static_cast<int>(posX);
//		moveRequestPacket.newPositionY = static_cast<int>(posY);
//		networkClient.sendPacket(moveRequestPacket);
//		currentTime = sf::Time::Zero;
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
	playerTextureProvider.storeResource(
			loadTextureFromPath(FilePath("dungeon_tiles.png"), sf::IntRect(197, 160, 16, 20)),
			playerTextureIDProvider.createNewMapping("GREEN"));

	map.loadMap(tokenize<ResourceID>(FilePath("testMap.txt")));
	player.move(20, 20);
	player.setPlayerTexture(playerTextureProvider.getResource(playerTextureIDProvider.getResourceID("GREEN")));

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
