#include "Game.hpp"

void Game::onTick() {
	//TODO
}

void Game::handlePacket(const ClientPacketWrapper& packetWrapper, PlayerID playerID) {
	//TODO
}

Game::Game(std::shared_ptr<NetworkManager> networkManager) : networkManager(std::move(networkManager)) {}
