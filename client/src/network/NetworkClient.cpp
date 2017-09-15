#include "NetworkClient.hpp"
#include "../../../shared/packets/HandshakeRequest.hpp"
#include "../../../shared/packets/HandshakeResponse.hpp"

bool NetworkClient::openConnection(sf::IpAddress address, unsigned short port) {
	closeConnection();
	serverAddress = address;
	serverPort = port;
	socket.bind(port);

	HandshakeRequestPacket handshakeRequestPacket;
	if (sendPacket(handshakeRequestPacket) != sf::Socket::Done) return false;

	receiveNewPacket();
	socket.setBlocking(false);

	HandshakeResponsePacket responsePacket;
	responsePacket.parsePacket(nextPacket);

	return responsePacket.responseCode == HandshakeResponsePacket::ResponseCode::SUCCESSFUL;
}

void NetworkClient::closeConnection() {
	// TODO send disconnect packet
	socket.unbind();
}

sf::Socket::Status NetworkClient::sendPacket(sf::Packet packet) {
//	return socket.send(packet, serverAddress, serverPort);
	return socket.send(packet, serverAddress, 54001); //TODO Change to regular port when not in debug mode
}

sf::Socket::Status NetworkClient::sendPacket(const Packet& packet) {
	return sendPacket(packet.generatePacket());
}

bool NetworkClient::receiveNewPacket() {
	return socket.receive(nextPacket, serverAddress, serverPort) == sf::Socket::Done;
}

sf::Packet NetworkClient::getRecentPacket() {
	return nextPacket;
}
