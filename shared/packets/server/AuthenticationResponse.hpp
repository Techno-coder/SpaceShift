#pragma once

#include <packets/ServerPacket.hpp>

struct AuthenticationResponsePacket : public ServerPacket {
	enum class Response : sf::Uint8 {
		SUCCESSFUL = 0,
		INVALID = 1
	} response = Response::SUCCESSFUL;

	ServerPacketWrapper::Type getType() const override {
		return ServerPacketWrapper::Type::AUTHENTICATION_RESPONSE;
	}

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
