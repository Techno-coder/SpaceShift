#pragma once

#include "../../ServerPacket.hpp"

struct LoginResponsePacket : public ServerPacket {
	enum class Response : sf::Uint8 {
		SUCCESSFUL = 0,
		INVALID = 1
	} response = Response::SUCCESSFUL;

	ServerPacketWrapper::Type getType() const override {
		return ServerPacketWrapper::Type::LOGIN_RESPONSE;
	}

	sf::Packet generatePacket() const override {
		sf::Packet packet;
		return packet << response;
	}

	void parsePacket(sf::Packet& packet) override {
		sf::Uint8 responseCode;
		packet >> responseCode;
		response = static_cast<Response>(responseCode);
	}
};
