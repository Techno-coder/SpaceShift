#pragma once

#include "Constants.hpp"
#include "PacketSender.hpp"
#include <utility/DoubleMap.hpp>
#include <packets/Packet.hpp>

#include <SFML/Network/IpAddress.hpp>
#include <map>
#include <memory>

class ServerPacket;

class ClientPacketWrapper;

class PacketHandler;

class NetworkManager : public PacketSender {
	struct PlayerData {
		sf::Time sinceLastPacket = sf::Time::Zero;
		bool keepAlivePacketSent = false;

		void resetTimeSinceLastPacket() {
			sinceLastPacket = sf::Time::Zero;
			keepAlivePacketSent = false;
		}
	};

	std::map<sf::IpAddress, sf::Time> notAuthenticated;

	DoubleMap<sf::IpAddress, PlayerID> playerIPs;
	std::map<PlayerID, PlayerData> playerData;

	std::shared_ptr<sf::UdpSocket> socket;
	std::vector<std::reference_wrapper<PacketHandler>> packetHandlers;

	void sendPacket(sf::Packet packet, const sf::IpAddress& address);

	void handleHandshake(sf::Packet& packet, sf::IpAddress address);
	void handleDisconnect(PlayerID playerID, const ClientPacketWrapper& disconnectPacketWrapper);

	void authenticate(ClientPacketWrapper& packet, sf::IpAddress address);
	bool waitingForAuthentication(sf::IpAddress address);
public:
	explicit NetworkManager(std::shared_ptr<sf::UdpSocket> socket);

	void onTick();
	void handlePacket(sf::Packet& packet, const sf::IpAddress& address);
	void registerPacketHandler(PacketHandler& packetHandler);

	void sendPacket(const ServerPacket& packet, const PlayerID& playerID) override;
};
