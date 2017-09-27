#include "Game.hpp"

#include "../PacketSender.hpp"
#include "../generator/SquareGenerator.hpp"

#include <utility/Serializer.hpp>
#include <packets/server/PlayerPositionsUpdate.hpp>
#include <packets/ClientPacketWrapper.hpp>
#include <packets/client/PlayerMoveRequest.hpp>
#include <packets/server/MapChangeEvent.hpp>
#include <packets/server/PlayerDisconnectNotify.hpp>

void Game::onTick() {
	//TODO
	sendPositions();
}

void Game::handlePacket(const ClientPacketWrapper& packetWrapper, const PlayerID& playerID) {
	//TODO
	typedef ClientPacketWrapper::Type Type;
	switch (packetWrapper.type) {
		case Type::MOVE_REQUEST: {
			//TODO make sure move is valid
			PlayerMoveRequestPacket moveRequestPacket;
			moveRequestPacket.parsePacket(packetWrapper.internal);
			joinedPlayers[playerID].positionX = moveRequestPacket.newPositionX;
			joinedPlayers[playerID].positionY = moveRequestPacket.newPositionY;
			break;
		}
		default:
			break;
	}
}

Game::Game(PacketSender& packetSender) : packetSender(packetSender) {
	//TODO load with proper map
	currentMap = getSquareMap(30, 30);
}

bool Game::hasStarted() const {
	return started;
}

void Game::start() {
	started = true;
	//TODO
}

std::vector<PlayerID> Game::getJoinedPlayers() const {
	std::vector<PlayerID> vector;
	vector.reserve(joinedPlayers.size());
	for (const auto& pair : joinedPlayers) {
		vector.push_back(pair.first);
	}
	return vector;
}

void Game::joinPlayer(PlayerID playerID) {
	joinedPlayers[playerID] = PlayerEntity();
	//TODO set health, spawn position, display name
	//TODO send information about other players
	MapChangeEventPacket mapChangeEventPacket;
	mapChangeEventPacket.serializedMapData = serialize<TileID>(currentMap);
	packetSender.sendPacket(mapChangeEventPacket, playerID);
}

void Game::removePlayer(PlayerID playerID) {
	joinedPlayers.erase(playerID);
	PlayerDisconnectNotifyPacket disconnectNotifyPacket;
	disconnectNotifyPacket.playerID = playerID;
	sendGlobalPacket(disconnectNotifyPacket);
}

unsigned long Game::getNumberOfJoinedPlayers() const {
	return joinedPlayers.size();
}

void Game::sendPositions() const {
	PlayerPositionsUpdatePacket positionsUpdatePacket;
	for (const auto& pair : joinedPlayers) {
		positionsUpdatePacket.playerPositions[pair.first] = {pair.second.positionX, pair.second.positionY};
	}
	sendGlobalPacket(positionsUpdatePacket);
}

void Game::sendGlobalPacket(const ServerPacket& packet) const {
	for (const auto& pair : joinedPlayers) packetSender.sendPacket(packet, pair.first);
}
