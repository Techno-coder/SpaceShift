#pragma once

#include <SFML/Network/Packet.hpp>

class Packet {
public:
	virtual sf::Packet generatePacket() const = 0;
	virtual void parsePacket(sf::Packet& packet) = 0;
};