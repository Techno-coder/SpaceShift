#pragma once

#include "Constants.hpp"
#include "GameManager.hpp"
#include "../../shared/utility/DoubleMap.hpp"
#include "../../shared/Packet.hpp"
#include "../../shared/ClientPacketWrapper.hpp"

#include <SFML/Network/IpAddress.hpp>
#include <map>

class GameManager;

class NetworkManager {
	std::map<sf::IpAddress, sf::Time> notAuthenticated;
	DoubleMap<sf::IpAddress, PlayerID> playerIPs;
	std::shared_ptr<sf::UdpSocket> socket;

	std::shared_ptr<GameManager> gameManager;

	void sendPacket(sf::Packet packet, sf::IpAddress address);

	void handleHandshake(sf::Packet& packet, sf::IpAddress address);
	void handleDisconnect(PlayerID playerID);
	void authenticate(ClientPacketWrapper& packet, sf::IpAddress address);
public:
	NetworkManager(std::shared_ptr<GameManager> gameManager, std::shared_ptr<sf::UdpSocket> socket);

	void handlePacket(sf::Packet& packet, sf::IpAddress address);
};

