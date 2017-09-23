#pragma once

#include <utility/Constants.hpp>

class ClientPacketWrapper;

class PacketHandler {
public:
	virtual void handlePacket(const ClientPacketWrapper& packetWrapper, const PlayerID& playerID) = 0;
};

