#include "NetworkClient.hpp"
#include "../../../shared/packets/HandshakeRequest.hpp"

bool NetworkClient::openConnection(sf::IpAddress address, unsigned short port) {
	closeConnection();
	serverAddress = address;
	serverPort = port;
	socket.bind(port);

	if (sendPacket(HandshakeRequestPacket()) != sf::Socket::Done) {
		return false;
	}
	return true;
}

void NetworkClient::closeConnection() {
	// TODO send disconnect packet
	socket.unbind();
}

sf::Socket::Status NetworkClient::sendPacket(sf::Packet packet) {
	return socket.send(packet, serverAddress, serverPort);
}

sf::Socket::Status NetworkClient::sendPacket(const Packet& packet) {
	return sendPacket(packet.generatePacket());
}
