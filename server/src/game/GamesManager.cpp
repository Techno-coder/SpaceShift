#include "GamesManager.hpp"

#include <packets/ClientPacketWrapper.hpp>

bool GameManager::isInGame(PlayerID playerID) {
	return inGamePlayers.count(playerID) != 0;
}

Game& GameManager::getGamePlayerIsIn(PlayerID playerID) {
	return *games.at(inGamePlayers.at(playerID));
}

void GameManager::onTick() {
	for (auto& pair : games) pair.second->onTick();
}

GameManager::GameManager(PacketSender& packetSender) : packetSender(packetSender) {}

void GameManager::handlePacket(const ClientPacketWrapper& packetWrapper, const PlayerID& playerID) {
	//TODO handle Game manager specific packets ie game join request
	typedef ClientPacketWrapper::Type Type;
	switch (packetWrapper.type) {
		case Type::DISCONNECT:
			disconnectPlayer(playerID);
			break;
		case Type::QUICK_JOIN_REQUEST:
			quickJoinPlayer(playerID);
			break;
		default:
			if (isInGame(playerID)) getGamePlayerIsIn(playerID).handlePacket(packetWrapper, playerID);
			break;
	}
}

bool GameManager::isInLobby(PlayerID playerID) {
	//TODO heck is this even needed?
	if (isInGame(playerID)) return getGamePlayerIsIn(playerID).hasStarted();
	return false;
}

void GameManager::disconnectPlayer(PlayerID playerID) {
	//TODO delete game if empty?
	if (!isInGame(playerID)) return;
	getGamePlayerIsIn(playerID).removePlayer(playerID);
	inGamePlayers.erase(playerID);
}

void GameManager::removeGame(GameID gameID) {
	//TODO is this even needed?
	if (games.count(gameID) == 0) return;
	Game& game = *games.at(gameID);
	for (const auto& player : game.getJoinedPlayers()) disconnectPlayer(player);
	games.erase(gameID);
}

GameID GameManager::createNewEmptyGame() {
	GameID randomID;
	do {
		randomID = static_cast<GameID>(rand());
	} while (games.count(randomID) != 0);
	games[randomID] = std::make_unique<Game>(packetSender);
	return randomID;
}

void GameManager::quickJoinPlayer(PlayerID playerID) {
	for (const auto& pair : lobbies) {
		if (games[pair.first]->getNumberOfJoinedPlayers() < MAXIMUM_PLAYERS_PER_GAME) {
			inGamePlayers[playerID] = pair.first;
			games[pair.first]->joinPlayer(playerID);
			return;
		}
	}

	auto gameID = createNewEmptyGame();
	lobbies[gameID] = LobbyData();
	inGamePlayers[playerID] = gameID;
	games[gameID]->joinPlayer(playerID);
}
