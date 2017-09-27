#include "NetworkManager.hpp"

#include "PacketHandler.hpp"
#include "Constants.hpp"
#include <packets/HandshakeRequest.hpp>
#include <packets/HandshakeResponse.hpp>
#include <packets/server/CheckAliveRequest.hpp>
#include <packets/server/AuthenticationResponse.hpp>
#include <packets/client/AuthenticationRequest.hpp>

#include <SFML/Network/UdpSocket.hpp>

void NetworkManager::handlePacket(sf::Packet& packet, const PlayerIdentifier& identifier) {
	static const auto handshakeRequestSize = HandshakeRequestPacket().generatePacket().getDataSize();
	if (packet.getDataSize() == handshakeRequestSize) return handleHandshake(packet, identifier);
	if (!playerIPs.exists(identifier) && !waitingForAuthentication(identifier)) return;

	ClientPacketWrapper packetWrapper;
	packetWrapper.parsePacket(packet);
	if (waitingForAuthentication(identifier)) return authenticate(packetWrapper, identifier);

	PlayerID playerID = playerIPs.get(identifier);
	playerData[playerID].resetTimeSinceLastPacket();

	if (packetWrapper.type == ClientPacketWrapper::Type::CHECK_ALIVE_RESPONSE) return;
	if (packetWrapper.type == ClientPacketWrapper::Type::DISCONNECT) return handleDisconnect(playerID, packetWrapper);
	for (auto& handler : packetHandlers) handler.get().handlePacket(packetWrapper, playerID);
}

void NetworkManager::handleHandshake(sf::Packet& packet, PlayerIdentifier identifier) {
	//TODO consider disconnecting the player before handshaking
	notAuthenticated.erase(identifier);

	HandshakeRequestPacket handshakeRequestPacket;
	handshakeRequestPacket.parsePacket(packet);

	HandshakeResponsePacket responsePacket;
	if (handshakeRequestPacket.protocolVersion == 0) {
		responsePacket.response = HandshakeResponsePacket::Response::SUCCESSFUL;
		notAuthenticated[identifier] = sf::Time::Zero;
	} else {
		responsePacket.response = HandshakeResponsePacket::Response::CLIENT_OUTDATED;
	}
	sendPacket(responsePacket.generatePacket(), identifier);
}

void NetworkManager::sendPacket(sf::Packet packet, const PlayerIdentifier& identifier) {
	socket->send(packet, identifier.first, identifier.second);
}

void NetworkManager::authenticate(ClientPacketWrapper& packet, PlayerIdentifier identifier) {
	if (packet.type != ClientPacketWrapper::Type::AUTHENTICATION_REQUEST) return;
	AuthenticationRequestPacket requestPacket;
	requestPacket.parsePacket(packet.internal);

	// TODO proper authentication with token
	notAuthenticated.erase(identifier);
	PlayerID totallyLegitPlayerID;
	do {
		totallyLegitPlayerID = static_cast<PlayerID>(rand());
	} while (playerIPs.exists(totallyLegitPlayerID));
	playerIPs.add(identifier, totallyLegitPlayerID); // TODO Proper player ids l m a o
	AuthenticationResponsePacket responsePacket;
	responsePacket.response = AuthenticationResponsePacket::Response::SUCCESSFUL;
	sendPacket(responsePacket, totallyLegitPlayerID);
}

void NetworkManager::handleDisconnect(PlayerID playerID, const ClientPacketWrapper& disconnectPacketWrapper) {
	for (auto& handler : packetHandlers) handler.get().handlePacket(disconnectPacketWrapper, playerID);
	playerData.erase(playerID);
	playerIPs.remove(playerID);
}

NetworkManager::NetworkManager(std::shared_ptr<sf::UdpSocket> socket) : socket(std::move(socket)) {}

void NetworkManager::onTick() {
	for (auto it = notAuthenticated.begin(); it != notAuthenticated.end();) {
		it->second += TICK_SPEED;
		if (it->second > AUTHENTICATION_TIMEOUT) {
			notAuthenticated.erase(it++);
			// TODO send packet indicating the client took too long to login
		} else ++it;
	}

	for (auto it = playerData.begin(); it != playerData.end();) {
		it->second.sinceLastPacket += TICK_SPEED;
		if (it->second.sinceLastPacket > DISCONNECT_TIMEOUT) {
			handleDisconnect(it++->first, ClientPacketWrapper());
			continue;
		}

		if (it->second.sinceLastPacket > KEEP_ALIVE_TIMEOUT && !it->second.keepAlivePacketSent) {
			it->second.keepAlivePacketSent = true;
			CheckAliveRequestPacket aliveRequestPacket;
			sendPacket(aliveRequestPacket, it->first);
		}
		++it;
	}
}

void NetworkManager::sendPacket(const ServerPacket& packet, const PlayerID& playerID) {
	ServerPacketWrapper packetWrapper;
	packetWrapper.type = packet.getType();
	packetWrapper.internal = packet.generatePacket();
	sendPacket(packetWrapper.generatePacket(), playerIPs.get(playerID));
}

bool NetworkManager::waitingForAuthentication(const PlayerIdentifier& identifier) {
	return notAuthenticated.count(identifier) > 0;
}

void NetworkManager::registerPacketHandler(PacketHandler& packetHandler) {
	packetHandlers.emplace_back(packetHandler);
}

