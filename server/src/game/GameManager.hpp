#pragma once

#include "Game.hpp"
#include "../Constants.hpp"

#include <map>

class Game;

class NetworkManager;

class GameManager : public PacketHandler {
	std::map<GameID, std::unique_ptr<Game>> games;
	std::map<PlayerID, GameID> inGamePlayers;

	PacketSender& packetSender;

	bool isInGame(PlayerID playerID);
	Game& getGamePlayerIsIn(PlayerID playerID);
public:
	explicit GameManager(PacketSender& packetSender);

	void handlePacket(const ClientPacketWrapper& packetWrapper, PlayerID playerID) override;
	void onTick();
};

