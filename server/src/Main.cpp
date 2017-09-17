#include "Constants.hpp"

#include "../../shared/packets/HandshakeResponse.hpp"
#include "Game.hpp"

#include <SFML/Network/UdpSocket.hpp>
#include <SFML/System/Clock.hpp>

#include <iostream>

int main() {
	std::shared_ptr<sf::UdpSocket> socket = std::make_shared<sf::UdpSocket>();
	if (socket->bind(SERVER_PORT) != sf::Socket::Done) return 1;
	socket->setBlocking(false);

	std::shared_ptr<NetworkManager> networkManager;
	std::shared_ptr<GameManager> gameManager = std::make_shared<GameManager>(networkManager);
	networkManager = std::make_shared<NetworkManager>(gameManager, socket);

	sf::Clock clock;
	sf::Time currentTime = sf::Time::Zero;
	while (true) {
		unsigned short port;
		sf::IpAddress ipAddress;
		sf::Packet packet;
		if (socket->receive(packet, ipAddress, port) == sf::Socket::Done)
			networkManager->handlePacket(packet, ipAddress);

		while (currentTime >= TICK_SPEED) {
			gameManager->onTick();
			networkManager->onTick();
			currentTime -= TICK_SPEED;
		}
		currentTime += clock.restart();
	}
	return 0;
}