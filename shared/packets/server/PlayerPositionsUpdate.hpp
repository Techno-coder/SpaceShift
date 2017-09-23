#pragma once

#include <packets/ServerPacket.hpp>
#include <utility/Constants.hpp>
#include <map>

struct PlayerPositionsUpdatePacket : public ServerPacket {
	std::map<PlayerID, std::pair<int, int>> playerPositions;

	ServerPacketWrapper::Type getType() const override {
		return ServerPacketWrapper::Type::PLAYER_POSITIONS_UPDATE;
	}

	sf::Packet generatePacket() const override {
		sf::Packet packet;
		packet << static_cast<sf::Int8>(playerPositions.size());
		for (const auto& pair : playerPositions) {
			packet << pair.first << pair.second.first << pair.second.second;
		}
		return packet;
	}

	void parsePacket(sf::Packet& packet) override {
		sf::Int8 mapSize;
		packet >> mapSize;
		for (int i = 0; i < mapSize; ++i) {
			PlayerID playerID;
			int x, y;
			packet >> playerID >> x >> y;
			playerPositions[playerID] = {x, y};
		}
	}
};