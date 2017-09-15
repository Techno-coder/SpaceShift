#include "../../shared/packets/HandshakeResponse.hpp"
#include "../../shared/packets/HandshakeRequest.hpp"
#include "../../shared/packets/server/MapChangeEvent.hpp"

#include <iostream>

#include <SFML/Network/UdpSocket.hpp>
#include <set>
#include <SFML/System/Clock.hpp>

sf::Socket::Status sendPacket(sf::UdpSocket& socket, sf::Packet packet, sf::IpAddress address, unsigned short port) {
//	return socket.send(packet, address, port);
	return socket.send(packet, address, 54000); // TODO Change when not in debug mode
}

int main() {
	unsigned short port;
	std::cout << "Please specify a port to bind to: " << std::endl;
	std::cin >> port;

	sf::UdpSocket socket;
	if (socket.bind(port) != sf::Socket::Done) return 1;

	sf::IpAddress ipAddress;
	sf::Packet packet;

	while (true) {
		socket.receive(packet, ipAddress, port);
		HandshakeRequestPacket requestPacket;
		requestPacket.parsePacket(packet);

		std::cout << "Handshake received" << std::endl;

		HandshakeResponsePacket responsePacket;
		responsePacket.response = HandshakeResponsePacket::Response::SUCCESSFUL;
		sendPacket(socket, responsePacket.generatePacket(), ipAddress, port);

		std::cout << "Response packet sent" << std::endl;

		sf::Clock clock;
		sf::Time elapsed = sf::Time::Zero;
		while (elapsed < sf::seconds(5)) {
			elapsed += clock.restart();
		}

		std::cout << "Clock finished" << std::endl;

		std::string mapData = "1 2 2 2 3\n8 1 1 1 7 2 2 2 3\n8 0 0 0 0 0 0 0 4\n8 0 0 0 1 6 6 6 5\n7 6 6 6 5";

		MapChangeEventPacket mapChangeEventPacket;
		mapChangeEventPacket.serializedMapData = mapData;

		ServerPacketWrapper packetWrapper;
		packetWrapper.internal = mapChangeEventPacket.generatePacket();
		packetWrapper.type = ServerPacketWrapper::Type::MAP_CHANGE_EVENT;

		sendPacket(socket, packetWrapper.generatePacket(), ipAddress, port);
		std::cout << "MAP_CHANGE_EVENT pack sent" << std::endl;
	}

	return 0;
}