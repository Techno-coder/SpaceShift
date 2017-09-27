#pragma once

#include <packets/ServerPacket.hpp>
#include <utility/Constants.hpp>

struct PlayerDisconnectNotifyPacket : public ServerPacket {
	PlayerID playerID = 0;

	ServerPacketWrapper::Type getType() const override {
		return ServerPacketWrapper::Type::PLAYER_DISCONNECT_NOTIFY;
	}

	sf::Packet generatePacket() const override {
		sf::Packet packet;
		packet << playerID;
		return packet;
	}

	void parsePacket(sf::Packet& packet) override {
		packet >> playerID;
	}
};