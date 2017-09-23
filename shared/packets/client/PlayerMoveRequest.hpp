#pragma once

#include <packets/ClientPacket.hpp>

struct PlayerMoveRequestPacket : public ClientPacket {
	int newPositionX = 0, newPositionY = 0;

	ClientPacketWrapper::Type getType() const override {
		return ClientPacketWrapper::Type::MOVE_REQUEST;
	}

	sf::Packet generatePacket() const override {
		sf::Packet packet;
		return packet << newPositionX << newPositionY;
	}

	void parsePacket(sf::Packet& packet) override {
		packet >> newPositionX >> newPositionY;
	}
};