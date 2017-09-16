#pragma once

#include "Constants.hpp"
#include "Game.hpp"
#include "NetworkManager.hpp"

#include <map>

class Game;

class NetworkManager;

class GameManager {
	std::map<GameID, std::unique_ptr<Game>> games;
	std::map<PlayerID, GameID> inGamePlayers;

	std::shared_ptr<NetworkManager> networkManager;
public:
	GameManager(std::shared_ptr<NetworkManager> networkManager);

	bool isInGame(PlayerID playerID);
	Game& getGamePlayerIsIn(PlayerID playerID);

	void onTick();
};

