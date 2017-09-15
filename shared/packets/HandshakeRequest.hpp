#pragma once

#include "../Packet.hpp"

#include <SFML/Config.hpp>

struct HandshakeRequestPacket : public Packet {
	sf::Uint16 protocolVersion = 0;

	sf::Packet generatePacket() const override {
		sf::Packet p;
		return p << protocolVersion;
	}

	void parsePacket(sf::Packet& packet) override {
		packet >> protocolVersion;
	}
};