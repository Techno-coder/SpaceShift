#pragma once

#include "../Packet.hpp"

struct HandshakeResponsePacket : public Packet {
	enum class ResponseCode : sf::Uint8 {
		SUCCESSFUL = 0,
		CLIENT_OUTDATED = 1
	} responseCode = ResponseCode::SUCCESSFUL;

	sf::Packet generatePacket() const override {
		sf::Packet packet;
		return packet << static_cast<sf::Uint8>(responseCode);
	}

	void parsePacket(sf::Packet& packet) override {
		sf::Uint8 response;
		packet >> response;
		responseCode = static_cast<ResponseCode>(response);
	}
};
