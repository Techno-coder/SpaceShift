#pragma once

#include "../../ClientPacket.hpp"

struct LoginRequestPacket : public ClientPacket { //TODO add encryption
	std::string authenticationToken;

	ClientPacketWrapper::Type getType() const override {
		return ClientPacketWrapper::Type::LOGIN_REQUEST;
	}

	sf::Packet generatePacket() const override {
		sf::Packet packet;
		return packet << authenticationToken;
	}

	void parsePacket(sf::Packet& packet) override {
		packet >> authenticationToken;
	}
};
