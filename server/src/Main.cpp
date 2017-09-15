#include "../../shared/packets/HandshakeResponse.hpp"
#include "../../shared/packets/HandshakeRequest.hpp"

#include <iostream>

#include <SFML/Network/UdpSocket.hpp>

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

		HandshakeResponsePacket responsePacket;
		responsePacket.responseCode == HandshakeResponsePacket::ResponseCode::SUCCESSFUL;
		sendPacket(socket, packet, ipAddress, port);
	}

	return 0;
}