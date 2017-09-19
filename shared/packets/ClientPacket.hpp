#pragma once

#include "ClientPacketWrapper.hpp"

class ClientPacket : public Packet {
public:
	virtual ClientPacketWrapper::Type getType() const = 0;
};
