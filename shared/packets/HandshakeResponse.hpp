#pragma once

#include "Packet.hpp"

struct HandshakeResponsePacket : public Packet {
	enum class Response : sf::Uint8 {
		SUCCESSFUL = 0,
		CLIENT_OUTDATED = 1
	} response = Response::SUCCESSFUL;

	sf::Packet generatePacket() const override {
		sf::Packet packet;
		return packet << static_cast<sf::Uint8>(response);
	}

	void parsePacket(sf::Packet& packet) override {
		sf::Uint8 responseCode;
		packet >> responseCode;
		response = static_cast<Response>(responseCode);
	}
};
