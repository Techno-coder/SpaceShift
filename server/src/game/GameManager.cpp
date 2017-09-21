#include "GameManager.hpp"

bool GameManager::isInGame(PlayerID playerID) {
	return inGamePlayers.count(playerID) != 0;
}

Game& GameManager::getGamePlayerIsIn(PlayerID playerID) {
	return *games[inGamePlayers[playerID]];
}

void GameManager::onTick() {
	for (auto& pair : games) pair.second->onTick();
}

GameManager::GameManager(PacketSender& packetSender) : packetSender(packetSender) {}

void GameManager::handlePacket(const ClientPacketWrapper& packetWrapper, PlayerID playerID) {
	//TODO
}
