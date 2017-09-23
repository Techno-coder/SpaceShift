#pragma once

#include <packets/ClientPacket.hpp>

struct QuickJoinRequestPacket : public ClientPacket {
	ClientPacketWrapper::Type getType() const override {
		return ClientPacketWrapper::Type::QUICK_JOIN_REQUEST;
	}

	sf::Packet generatePacket() const override {
		return sf::Packet();
	}

	void parsePacket(sf::Packet& packet) override {}
};