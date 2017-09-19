#include "Constants.hpp"
#include "game/GameManager.hpp"

#include <SFML/Network/UdpSocket.hpp>
#include <SFML/System/Clock.hpp>
#include <thread>

void gameUpdateThread(GameManager& gameManager) {
	while (true) {
		auto time = std::chrono::steady_clock::now() + std::chrono::milliseconds(TICK_SPEED.asMilliseconds());
		gameManager.onTick();
		std::this_thread::sleep_until(time);
	}
}

void networkUpdateThread(NetworkManager& networkManager) {
	while (true) {
		auto time = std::chrono::steady_clock::now() + std::chrono::milliseconds(TICK_SPEED.asMilliseconds());
		networkManager.onTick();
		std::this_thread::sleep_until(time);
	}
}

void networkThread(NetworkManager& networkManager, sf::UdpSocket& socket) {
	while (true) {
		unsigned short port;
		sf::IpAddress ipAddress;
		sf::Packet packet;
		if (socket.receive(packet, ipAddress, port) == sf::Socket::Done) {
			networkManager.handlePacket(packet, ipAddress);
		}
	}
}

int main() {
	std::shared_ptr<sf::UdpSocket> socket = std::make_shared<sf::UdpSocket>();
	if (socket->bind(SERVER_PORT) != sf::Socket::Done) return 1;
	socket->setBlocking(true);

	std::shared_ptr<NetworkManager> networkManager;
	std::shared_ptr<GameManager> gameManager = std::make_shared<GameManager>(networkManager);
	networkManager = std::make_shared<NetworkManager>(gameManager, socket);

	std::thread gameUpdate([&]() { gameUpdateThread(*gameManager); });
	std::thread networkUpdate([&]() { networkUpdateThread(*networkManager); });
	networkThread(*networkManager, *socket);
	gameUpdate.join();
	return 0;
}