#pragma once

#include "../../ClientPacket.hpp"

struct DisconnectNotifyPacket : public ClientPacket {
	ClientPacketWrapper::Type getType() const override {
		return ClientPacketWrapper::Type::DISCONNECT;
	}

	sf::Packet generatePacket() const override {
		return sf::Packet();
	}

	void parsePacket(sf::Packet& packet) override {}
};
