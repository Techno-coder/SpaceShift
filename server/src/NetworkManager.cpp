#include "NetworkManager.hpp"
#include "../../shared/packets/HandshakeRequest.hpp"
#include "../../shared/packets/HandshakeResponse.hpp"
#include "../../shared/packets/client/AuthenticationRequest.hpp"

#include <SFML/Network/UdpSocket.hpp>

void NetworkManager::handlePacket(sf::Packet& packet, sf::IpAddress address) {
	if (!playerIPs.exists(address)) handleHandshake(packet, address);
	ClientPacketWrapper packetWrapper;
	packetWrapper.parsePacket(packet);
	if (notAuthenticated.count(address) > 0) authenticate(packetWrapper, address);

	PlayerID playerID = playerIPs.get(address);
	if (packetWrapper.type == ClientPacketWrapper::Type::DISCONNECT) handleDisconnect(playerID);
	if (gameManager->isInGame(playerID)) gameManager->getGamePlayerIsIn(playerID).handlePacket(packetWrapper, playerID);
	// TODO handle a different kind of packet (eg game join request)
}

void NetworkManager::handleHandshake(sf::Packet& packet, sf::IpAddress address) {
	HandshakeRequestPacket handshakeRequestPacket;
	handshakeRequestPacket.parsePacket(packet);

	HandshakeResponsePacket responsePacket;
	if (handshakeRequestPacket.protocolVersion == 0) {
		responsePacket.response = HandshakeResponsePacket::Response::SUCCESSFUL;
		notAuthenticated[address] = sf::Time::Zero;
	} else {
		responsePacket.response = HandshakeResponsePacket::Response::CLIENT_OUTDATED;
	}
	sendPacket(responsePacket.generatePacket(), address);
}

void NetworkManager::sendPacket(sf::Packet packet, sf::IpAddress address) {
//	socket->send(packet, address, SERVER_PORT);
	socket->send(packet, address, SERVER_PORT - 1); //TODO DEBUG ONLY!!
}

void NetworkManager::authenticate(ClientPacketWrapper& packet, sf::IpAddress address) {
	if (packet.type != ClientPacketWrapper::Type::AUTHENTICATION_REQUEST) return;
	AuthenticationRequestPacket requestPacket;
	requestPacket.parsePacket(packet.internal);

	// TODO proper authentication with token
	notAuthenticated.erase(address);
	PlayerID totallyLegitPlayerID;
	do {
		totallyLegitPlayerID = static_cast<PlayerID>(rand());
	} while (playerIPs.exists(totallyLegitPlayerID));
	playerIPs.add(address, totallyLegitPlayerID); // TODO Proper player ids l m a o
}

void NetworkManager::handleDisconnect(PlayerID playerID) {
	//TODO
}

NetworkManager::NetworkManager(std::shared_ptr<GameManager> gameManager, std::shared_ptr<sf::UdpSocket> socket)
		: socket(std::move(socket)), gameManager(std::move(gameManager)) {}
