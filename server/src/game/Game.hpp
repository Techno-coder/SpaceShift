#pragma once

#include "../Constants.hpp"

#include <utility/MatrixVector.hpp>
#include <player/PlayerEntity.hpp>

#include <map>

typedef int TileID;

class ClientPacketWrapper;

class NetworkManager;

class Game {
	MatrixVector<TileID> currentMap;
	std::map<PlayerID, PlayerEntity> joinedPlayers;

	std::shared_ptr<NetworkManager> networkManager;
public:
	explicit Game(std::shared_ptr<NetworkManager> networkManager);

	void onTick();
	void handlePacket(const ClientPacketWrapper& packetWrapper, PlayerID playerID);
};
