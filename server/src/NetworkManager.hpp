#pragma once

#include "PacketSender.hpp"
#include <utility/DoubleMap.hpp>
#include <packets/Packet.hpp>

#include <SFML/Network/IpAddress.hpp>
#include <map>
#include <memory>

class ServerPacket;

class ClientPacketWrapper;

class PacketHandler;

typedef std::pair<sf::IpAddress, unsigned short> PlayerIdentifier;

class NetworkManager : public PacketSender {
	const sf::Time AUTHENTICATION_TIMEOUT = sf::seconds(5.0f);
	const sf::Time KEEP_ALIVE_TIMEOUT = sf::seconds(10.0f);
	const sf::Time DISCONNECT_TIMEOUT = sf::seconds(20.0f);

	struct PlayerData {
		sf::Time sinceLastPacket = sf::Time::Zero;
		bool keepAlivePacketSent = false;

		void resetTimeSinceLastPacket() {
			sinceLastPacket = sf::Time::Zero;
			keepAlivePacketSent = false;
		}
	};

	std::map<PlayerIdentifier, sf::Time> notAuthenticated;

	DoubleMap<PlayerIdentifier, PlayerID> playerIPs;
	std::map<PlayerID, PlayerData> playerData;

	std::shared_ptr<sf::UdpSocket> socket;
	std::vector<std::reference_wrapper<PacketHandler>> packetHandlers;

	void sendPacket(sf::Packet packet, const PlayerIdentifier& identifier);

	void handleHandshake(sf::Packet& packet, PlayerIdentifier identifier);
	void handleDisconnect(PlayerID playerID, const ClientPacketWrapper& disconnectPacketWrapper);

	void authenticate(ClientPacketWrapper& packet, PlayerIdentifier identifier);
	bool waitingForAuthentication(const PlayerIdentifier& identifier);
public:
	explicit NetworkManager(std::shared_ptr<sf::UdpSocket> socket);

	void onTick();
	void handlePacket(sf::Packet& packet, const PlayerIdentifier& identifier);
	void registerPacketHandler(PacketHandler& packetHandler);

	void sendPacket(const ServerPacket& packet, const PlayerID& playerID) override;
};
