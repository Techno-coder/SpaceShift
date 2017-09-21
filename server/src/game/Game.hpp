#pragma once

#include "../Constants.hpp"
#include "../PacketHandler.hpp"

#include <utility/MatrixVector.hpp>
#include <player/PlayerEntity.hpp>

#include <map>

typedef int TileID;

class ClientPacketWrapper;

class NetworkManager;

class PacketSender;

class Game : public PacketHandler {
	MatrixVector<TileID> currentMap;
	std::map<PlayerID, PlayerEntity> joinedPlayers;

	PacketSender& packetSender;
public:
	explicit Game(PacketSender& packetSender);

	void onTick();
	void handlePacket(const ClientPacketWrapper& packetWrapper, PlayerID playerID) override;
};
