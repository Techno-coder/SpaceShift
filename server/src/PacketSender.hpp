#pragma once

#include "Constants.hpp"

class ServerPacket;

class PacketSender {
public:
	virtual void sendPacket(const ServerPacket& packet, const PlayerID& playerID) = 0;
};