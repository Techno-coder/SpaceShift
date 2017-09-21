#include "Game.hpp"

void Game::onTick() {
	//TODO
}

void Game::handlePacket(const ClientPacketWrapper& packetWrapper, PlayerID playerID) {
	//TODO
}

Game::Game(PacketSender& packetSender) : packetSender(packetSender) {}
