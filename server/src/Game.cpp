#include "Game.hpp"

void Game::onTick() {
	//TODO
}

void Game::handlePacket(ClientPacketWrapper packetWrapper, PlayerID playerID) {
	//TODO
}

Game::Game(std::shared_ptr<NetworkManager> networkManager) : networkManager(std::move(networkManager)) {}
