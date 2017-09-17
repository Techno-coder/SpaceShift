#pragma once

#include "../../ClientPacket.hpp"

struct CheckAliveResponsePacket : public ClientPacket {
	ClientPacketWrapper::Type getType() const override {
		return ClientPacketWrapper::Type::CHECK_ALIVE_RESPONSE;
	}

	sf::Packet generatePacket() const override {
		return sf::Packet();
	}

	void parsePacket(sf::Packet& packet) override {}
};