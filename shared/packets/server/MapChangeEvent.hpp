#pragma once

#include <packets/ServerPacket.hpp>

struct MapChangeEventPacket : public ServerPacket { //TODO consider parsing map data in here
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