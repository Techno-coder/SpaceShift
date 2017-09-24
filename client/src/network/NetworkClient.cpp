#include "NetworkClient.hpp"

#include <SFML/System/Clock.hpp>

#include <packets/HandshakeRequest.hpp>
#include <packets/HandshakeResponse.hpp>
#include <packets/client/DisconnectNotify.hpp>

bool NetworkClient::openConnection(sf::IpAddress address, unsigned short port) {
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
	DisconnectNotifyPacket disconnectNotifyPacket;
	sendPacket(disconnectNotifyPacket);
	socket.unbind();
}

sf::Socket::Status NetworkClient::sendPacket(sf::Packet packet) {
#ifdef NDEBUG
	return socket.send(packet, serverAddress, serverPort);
#else
	return socket.send(packet, serverAddress, 54001);
#endif
}

sf::Socket::Status NetworkClient::sendPacket(const ClientPacket& packet) {
	ClientPacketWrapper wrapper;
	wrapper.internal = packet.generatePacket();
	wrapper.type = packet.getType();
	//TODO set sequence of packet

	return sendPacket(wrapper.generatePacket());
}

bool NetworkClient::receiveNewPacket() {
	sf::IpAddress ipAddress;
	unsigned short port;
	return socket.receive(nextPacket, ipAddress, port) == sf::Socket::Done;
}

ServerPacketWrapper NetworkClient::getRecentPacket() {
	ServerPacketWrapper wrapper;
	wrapper.parsePacket(nextPacket);
	return wrapper;
}
