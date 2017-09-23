#include "TestState.hpp"
#include "../resource/ResourceLoaders.hpp"

#include <packets/server/MapChangeEvent.hpp>
#include <packets/client/PlayerMoveRequest.hpp>
#include <utility/Tokenizer.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <packets/client/QuickJoinRequest.hpp>
#include <packets/client/AuthenticationRequest.hpp>
#include <packets/server/AuthenticationResponse.hpp>
#include <packets/server/PlayerPositionsUpdate.hpp>

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
	while (networkClient.receiveNewPacket()) {
		ServerPacketWrapper newPacket = networkClient.getRecentPacket();
		typedef ServerPacketWrapper::Type Type;
		switch (newPacket.type) {
			case Type::MAP_CHANGE_EVENT: {
				printf("MAP_CHANGE_EVENT packet received\n");
				MapChangeEventPacket mapChangeEventPacket;
				mapChangeEventPacket.parsePacket(newPacket.internal);
				map.loadMap(tokenize<ResourceID>(mapChangeEventPacket.serializedMapData));
				break;
			}
			case Type::PLAYER_POSITIONS_UPDATE: {
				PlayerPositionsUpdatePacket positionsUpdatePacket;
				positionsUpdatePacket.parsePacket(newPacket.internal);
				for (const auto& pair : positionsUpdatePacket.playerPositions) {
					multiplayerSprites[pair.first].setPosition(pair.second.first, pair.second.second);
					multiplayerSprites[pair.first].setSize(sf::Vector2f(20, 20));
					multiplayerSprites[pair.first].setFillColor(sf::Color::Red);
				}
				break;
			}
			case Type::AUTHENTICATION_RESPONSE: {
				AuthenticationResponsePacket responsePacket;
				responsePacket.parsePacket(newPacket.internal);
				if (responsePacket.response == AuthenticationResponsePacket::Response::SUCCESSFUL) {
					printf("AUTHENTICATION OK\n");
				} else {
					printf("AUTHENTICATION BAD\n");
				}

				QuickJoinRequestPacket quickJoinRequestPacket;
				networkClient.sendPacket(quickJoinRequestPacket);
				break;
			}
			case Type::CHECK_ALIVE_REQUEST: {
				printf("CHECK ALIVE REQUEST RECEIVED\n");
//				CheckAliveResponsePacket responsePacket;
//				networkClient.sendPacket(responsePacket);
				break;
			}
			default:
				break;
		}
	}
	currentTime += networkClock.restart();
	if (currentTime > sf::milliseconds(100)) {
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
	for (const auto& pair : multiplayerSprites) {
		target.draw(pair.second);
	}
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

	AuthenticationRequestPacket authenticationRequestPacket;
	authenticationRequestPacket.authenticationToken = "POO_YOU_SUCKER";
	networkClient.sendPacket(authenticationRequestPacket);
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
