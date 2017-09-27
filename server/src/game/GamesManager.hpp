#pragma once

#include "Game.hpp"
#include "../PacketHandler.hpp"

#include <SFML/System/Time.hpp>
#include <map>

class PacketSender;

typedef sf::Uint16 GameID;
const sf::Time TIME_BEFORE_GAME_START = sf::seconds(30.0f);
constexpr unsigned long MAXIMUM_PLAYERS_PER_GAME = 8;

class GameManager : public PacketHandler {
	struct LobbyData {
		bool isStarting = false;
		sf::Time timeBeforeStart = TIME_BEFORE_GAME_START;
	};

	std::map<GameID, LobbyData> lobbies;
	std::map<GameID, std::unique_ptr<Game>> games;
	std::map<PlayerID, GameID> inGamePlayers;

	PacketSender& packetSender;

	GameID createNewEmptyGame();

	/**
	 * Handle a quick join request by a player
	 * @param playerID The player who requested to quick join
	 */
	void quickJoinPlayer(PlayerID playerID);
	/**
	 * Disconnects all players in the game
	 * Removes the game instance if it exists
	 * @param gameID The game to remove
	 */
	void removeGame(GameID gameID);
	/**
	 * Remove the player from all games if they are in any
	 * @param playerID The player to disconnect
	 */
	void disconnectPlayer(PlayerID playerID);

	/**
	 * Checks if the player is in a lobby game
	 * @param playerID The player to check
	 * @return False if the player is not in a lobby game
	 */
	bool isInLobby(PlayerID playerID);
	/**
	 * Checks if the player is in a regular or lobby game
	 * @param playerID The player to check
	 * @return True if the player is in a regular or lobby game
	 */
	bool isInGame(PlayerID playerID);
	/**
	 * Gets the game or lobby that a player is in
	 * @throws out_of_range when player is not in a game
	 * @param playerID The playerID of the player
	 * @return The game object that contains the player
	 */
	Game& getGamePlayerIsIn(PlayerID playerID);
public:
	explicit GameManager(PacketSender& packetSender);

	void handlePacket(const ClientPacketWrapper& packetWrapper, const PlayerID& playerID) override;
	void onTick();
};

