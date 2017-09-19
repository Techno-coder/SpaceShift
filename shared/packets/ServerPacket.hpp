#pragma once

#include "ServerPacketWrapper.hpp"

class ServerPacket : public Packet {
public:
	virtual ServerPacketWrapper::Type getType() const = 0;
};
