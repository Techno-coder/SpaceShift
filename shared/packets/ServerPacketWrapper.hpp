#pragma once

#include "PacketWrapper.hpp"

class ServerPacketWrapper : public PacketWrapper {
public:
	enum class Type : sf::Uint16 {
		AUTHENTICATION_RESPONSE = 0,
		CHECK_ALIVE_REQUEST = 1,
		MAP_CHANGE_EVENT = 5,
		PLAYER_POSITIONS_UPDATE = 6,
		PLAYER_DISCONNECT_NOTIFY = 7
	} type;

private:
	sf::Uint16 getType() const override {
		return static_cast<sf::Uint16>(type);
	}

	void setType(sf::Uint16 newType) override {
		type = static_cast<Type>(newType);
	}
};