#pragma once

#include "../../ServerPacket.hpp"

struct MapChangeEventPacket : public ServerPacket {
	std::string serializedMapData;

	ServerPacketWrapper::Type getType() const override {
		return ServerPacketWrapper::Type::MAP_CHANGE_EVENT;
	}

	sf::Packet generatePacket() const override {
		sf::Packet packet;
		return packet << serializedMapData;
	}

	void parsePacket(sf::Packet& packet) override {
		packet >> serializedMapData;
	}
};