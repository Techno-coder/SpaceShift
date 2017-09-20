#pragma once

#include "Constants.hpp"
#include "game/GameManager.hpp"
#include <utility/DoubleMap.hpp>
#include <packets/Packet.hpp>

#include <SFML/Network/IpAddress.hpp>
#include <map>

class ServerPacket;

class GameManager;

class NetworkManager {
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
	std::shared_ptr<GameManager> gameManager;

	void sendPacket(sf::Packet packet, const sf::IpAddress& address);
	void sendPacket(const ServerPacket& packet, const PlayerID& playerID);

	void handleHandshake(sf::Packet& packet, sf::IpAddress address);
	void handleDisconnect(PlayerID playerID);

	void authenticate(ClientPacketWrapper& packet, sf::IpAddress address);
	bool waitingForAuthentication(sf::IpAddress address);
public:
	NetworkManager(std::shared_ptr<GameManager> gameManager, std::shared_ptr<sf::UdpSocket> socket);

	void onTick();
	void handlePacket(sf::Packet& packet, const sf::IpAddress& address);
};
