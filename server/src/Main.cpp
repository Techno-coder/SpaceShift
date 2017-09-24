#include "Constants.hpp"
#include "game/GamesManager.hpp"
#include "NetworkManager.hpp"

#include <SFML/Network/UdpSocket.hpp>
#include <SFML/System/Clock.hpp>
#include <mutex>
#include <thread>

std::mutex networkManagerMutex;

void updateState(NetworkManager& networkManager, GameManager& gameManager) {
	auto time = std::chrono::steady_clock::now() + std::chrono::milliseconds(TICK_SPEED.asMilliseconds());
	std::lock_guard<std::mutex> guard(networkManagerMutex);
	networkManager.onTick();
	gameManager.onTick();
	std::this_thread::sleep_until(time);
}

void socketListen(sf::UdpSocket& socket, NetworkManager& networkManager) {
	unsigned short port;
	sf::IpAddress ipAddress;
	sf::Packet packet;
	while (socket.receive(packet, ipAddress, port) == sf::Socket::Done) {
		std::lock_guard<std::mutex> guard(networkManagerMutex);
		networkManager.handlePacket(packet, ipAddress);
	}
}

int main() {
	srand(time(nullptr));

	std::shared_ptr<sf::UdpSocket> socket = std::make_shared<sf::UdpSocket>();
	if (socket->bind(SERVER_PORT) != sf::Socket::Done) return 1;
	socket->setBlocking(true);

	NetworkManager networkManager(socket);
	GameManager gameManager(networkManager);
	networkManager.registerPacketHandler(gameManager);

	auto socketListenWrapper = [&]() { while (true) socketListen(*socket, networkManager); };
	auto updateStateWrapper = [&]() { while (true) updateState(networkManager, gameManager); };
	std::thread socketThread(socketListenWrapper);
	std::thread updateThread(updateStateWrapper);
	socketThread.join();
	updateThread.join();
	return 0;
}