#pragma once

#include "PacketWrapper.hpp"

class ClientPacketWrapper : public PacketWrapper {
public:
	enum class Type : sf::Uint16 {
		DISCONNECT = 0,
		LOGIN_REQUEST = 1
	} type = Type::DISCONNECT;

private:
	sf::Uint16 getType() const override {
		return static_cast<sf::Uint16>(type);
	}

	void setType(sf::Uint16 newType) override {
		type = static_cast<Type>(newType);
	}
};