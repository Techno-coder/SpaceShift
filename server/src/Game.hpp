#pragma once

#include "Constants.hpp"
#include "NetworkManager.hpp"

#include "../../shared/utility/MatrixVector.hpp"
#include "../../shared/player/PlayerEntity.hpp"
#include "../../shared/ClientPacketWrapper.hpp"

#include <map>

typedef int TileID;

class NetworkManager;

class Game {
	MatrixVector<TileID> currentMap;
	std::map<PlayerID, PlayerEntity> joinedPlayers;

	std::shared_ptr<NetworkManager> networkManager;
public:
	Game(std::shared_ptr<NetworkManager> networkManager);

	void onTick();
	void handlePacket(ClientPacketWrapper packetWrapper, PlayerID playerID);
};
