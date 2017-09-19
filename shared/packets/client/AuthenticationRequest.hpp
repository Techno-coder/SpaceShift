#pragma once

#include "packets/ClientPacket.hpp"

struct AuthenticationRequestPacket : public ClientPacket { //TODO add encryption
	std::string authenticationToken;

	ClientPacketWrapper::Type getType() const override {
		return ClientPacketWrapper::Type::AUTHENTICATION_REQUEST;
	}

	sf::Packet generatePacket() const override {
		sf::Packet packet;
		return packet << authenticationToken;
	}

	void parsePacket(sf::Packet& packet) override {
		packet >> authenticationToken;
	}
};
