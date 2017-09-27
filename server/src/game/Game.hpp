#pragma once

#include "../PacketHandler.hpp"

#include <utility/MatrixVector.hpp>
#include <utility/Constants.hpp>
#include <player/PlayerEntity.hpp>
#include <packets/ServerPacket.hpp>

#include <map>

typedef int TileID;

class ClientPacketWrapper;

class PacketSender;

class Game : public PacketHandler {
	bool started = false;

	MatrixVector<TileID> currentMap;
	std::map<PlayerID, PlayerEntity> joinedPlayers;

	PacketSender& packetSender;

	void sendPositions() const;
	void sendGlobalPacket(const ServerPacket& packet) const;
public:
	explicit Game(PacketSender& packetSender);

	void onTick();
	void handlePacket(const ClientPacketWrapper& packetWrapper, const PlayerID& playerID) override;

	void start();
	bool hasStarted() const;

	/**
	 * Adds a player to this game
	 * @param playerID The player to add
	 */
	void joinPlayer(PlayerID playerID);
	/**
	 * Removes a player if they are in this game
	 * @param playerID The player to remove
	 */
	void removePlayer(PlayerID playerID);

	std::vector<PlayerID> getJoinedPlayers() const;
	unsigned long getNumberOfJoinedPlayers() const;
};
