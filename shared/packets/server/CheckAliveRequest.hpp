#pragma once

#include "../../ServerPacket.hpp"

struct CheckAliveRequestPacket : public ServerPacket {
	ServerPacketWrapper::Type getType() const override {
		return ServerPacketWrapper::Type::CHECK_ALIVE_REQUEST;
	}

	sf::Packet generatePacket() const override {
		return sf::Packet();
	}

	void parsePacket(sf::Packet& packet) override {}
};