#pragma once

#include "../../../shared/ServerPacketWrapper.hpp"

#include <SFML/Network/UdpSocket.hpp>
#include <SFML/Network/Packet.hpp>

class ClientPacket;

class NetworkClient {
	sf::UdpSocket socket;
	sf::IpAddress serverAddress;
	unsigned short serverPort;

	sf::Packet nextPacket;
public:
	/**
	 * Closes the current connection if one exists
	 */
	void closeConnection();
	/**
	 * Attempts to handshake with the server and start a connection
	 * @param address The address of the server
	 * @param port The port that the server is listening on
	 * @return False if the handshake was unsuccessful
	 */
	bool openConnection(sf::IpAddress address, unsigned short port);

	sf::Socket::Status sendPacket(sf::Packet packet);
	sf::Socket::Status sendPacket(const ClientPacket& packet);

	/**
	 * Attempts to receive a new packet
	 * @return True if a new packet was received
	 */
	bool receiveNewPacket();
	/**
	 * Gets the most recent packet received and parses it
	 * @return The most recent packet
	 */
	ServerPacketWrapper getRecentPacket();
};

