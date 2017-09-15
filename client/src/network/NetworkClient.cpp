#include "NetworkClient.hpp"

#include <SFML/System/Clock.hpp>

#include "../../../shared/packets/HandshakeRequest.hpp"
#include "../../../shared/packets/HandshakeResponse.hpp"
#include "../../../shared/packets/client/DisconnectNotify.hpp"

bool NetworkClient::openConnection(sf::IpAddress address, unsigned short port) {
	closeConnection();
	serverAddress = address;
	serverPort = port;
	socket.bind(port);

	HandshakeRequestPacket handshakeRequestPacket;
	if (sendPacket(handshakeRequestPacket.generatePacket()) != sf::Socket::Done) return false;

	sf::Clock clock;
	sf::Time elapsedTime = sf::Time::Zero;
	const sf::Time timeout = sf::seconds(10);

	socket.setBlocking(false);
	while (!receiveNewPacket()) {
		elapsedTime += clock.restart();
		if (elapsedTime > timeout) return false;
	}

	HandshakeResponsePacket responsePacket;
	responsePacket.parsePacket(nextPacket);

	return responsePacket.response == HandshakeResponsePacket::Response::SUCCESSFUL;
}

void NetworkClient::closeConnection() {
//	DisconnectNotifyPacket disconnectNotifyPacket;
//	sendPacket(disconnectNotifyPacket);
	socket.unbind();
}

sf::Socket::Status NetworkClient::sendPacket(sf::Packet packet) {
//	return socket.send(packet, serverAddress, serverPort);
	return socket.send(packet, serverAddress, 54001); //TODO Change to regular port when not in debug mode
}

sf::Socket::Status NetworkClient::sendPacket(const ClientPacket& packet) {
	ClientPacketWrapper wrapper;
	wrapper.internal = packet.generatePacket();
	wrapper.type = packet.getType();
	//TODO set sequence of packet

	return sendPacket(wrapper.generatePacket());
}

bool NetworkClient::receiveNewPacket() {
	return socket.receive(nextPacket, serverAddress, serverPort) == sf::Socket::Done;
}

ServerPacketWrapper NetworkClient::getRecentPacket() {
	ServerPacketWrapper wrapper;
	wrapper.parsePacket(nextPacket);
	return wrapper;
}
