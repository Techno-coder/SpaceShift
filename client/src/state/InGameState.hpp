#pragma once

#include "../State.hpp"
#include "../tilemap/TileMap.hpp"
#include "../level/Map.hpp"

class InGameState : public State {
	TileMap currentTileMap;
	Map currentMap;
public:
	void onEnter() override;
	void handleEvent(sf::Event& event, sf::RenderTarget& target) override;
	void update() override;
	void draw(sf::RenderTarget& target) override;
};

