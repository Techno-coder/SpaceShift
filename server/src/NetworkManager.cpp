#include "NetworkManager.hpp"
#include "game/GameManager.hpp"
#include <packets/HandshakeRequest.hpp>
#include <packets/HandshakeResponse.hpp>
#include <packets/client/AuthenticationRequest.hpp>
#include <packets/server/CheckAliveRequest.hpp>

#include <SFML/Network/UdpSocket.hpp>

void NetworkManager::handlePacket(sf::Packet& packet, const sf::IpAddress& address) {
	static const auto handshakeRequestSize = HandshakeRequestPacket().generatePacket().getDataSize();
	if (packet.getDataSize() == handshakeRequestSize) return handleHandshake(packet, address);
	if (!playerIPs.exists(address)) return;

	ClientPacketWrapper packetWrapper;
	packetWrapper.parsePacket(packet);
	if (waitingForAuthentication(address)) return authenticate(packetWrapper, address);

	PlayerID playerID = playerIPs.get(address);
	playerData[playerID].resetTimeSinceLastPacket();

	if (packetWrapper.type == ClientPacketWrapper::Type::DISCONNECT) return handleDisconnect(playerID);
	for (auto& handler : packetHandlers) handler.get().handlePacket(packetWrapper, playerID);
}

void NetworkManager::handleHandshake(sf::Packet& packet, sf::IpAddress address) {
	notAuthenticated.erase(address);

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

void NetworkManager::sendPacket(sf::Packet packet, const sf::IpAddress& address) {
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
	playerData.erase(playerID);
	playerIPs.remove(playerID);
	//TODO remove from any connected games
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
			handleDisconnect(it++->first);
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

bool NetworkManager::waitingForAuthentication(sf::IpAddress address) {
	return notAuthenticated.count(address) > 0;
}

void NetworkManager::registerPacketHandler(PacketHandler& packetHandler) {
	packetHandlers.push_back(packetHandler);
}
