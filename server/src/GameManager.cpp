#include "GameManager.hpp"

#include <utility>

bool GameManager::isInGame(PlayerID playerID) {
	return inGamePlayers.count(playerID) != 0;
}

Game& GameManager::getGamePlayerIsIn(PlayerID playerID) {
	return *games[inGamePlayers[playerID]];
}

GameManager::GameManager(std::shared_ptr<NetworkManager> networkManager) : networkManager(std::move(networkManager)) {}

void GameManager::onTick() {
	for (auto& pair : games) pair.second->onTick();
}
