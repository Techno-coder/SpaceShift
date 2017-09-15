#pragma once

#include "Packet.hpp"

#include <memory>

class PacketWrapper : public Packet {
	virtual sf::Uint16 getType() const = 0;
	virtual void setType(sf::Uint16 newType) = 0;

public:
	sf::Uint8 sequence{};
	mutable sf::Packet internal{};

	sf::Packet generatePacket() const override {
		sf::Packet packet;
		packet << sequence << getType();

		while (!internal.endOfPacket()) {
			sf::Uint8 byte;
			internal >> byte;
			packet << byte;
		}
		return packet;
	}

	void parsePacket(sf::Packet& packet) override {
		sf::Uint16 type;
		packet >> sequence >> type;
		setType(type);

		while (!packet.endOfPacket()) {
			sf::Uint8 byte;
			packet >> byte;
			internal << byte;
		}
	}
};

