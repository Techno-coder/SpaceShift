#pragma once

#include "../../ServerPacket.hpp"

struct PlayerPositionsUpdatePacket : public ServerPacket { // TODO
	ServerPacketWrapper::Type getType() const override {
		return ServerPacketWrapper::Type::PLAYER_POSITIONS_UPDATE;
	}

	sf::Packet generatePacket() const override {
		return nullptr;
	}

	void parsePacket(sf::Packet& packet) override {

	}
};