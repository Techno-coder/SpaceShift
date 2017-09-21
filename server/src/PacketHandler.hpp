#pragma once

#include "Constants.hpp"

class ClientPacketWrapper;

class PacketHandler {
public:
	virtual void handlePacket(const ClientPacketWrapper& packetWrapper, PlayerID playerID) = 0;
};

