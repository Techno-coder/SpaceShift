#pragma once

#include "../State.hpp"
#include "../Tilemap.hpp"

class InGameState : public State {
	Tilemap currentMap;
public:
	void onEnter() override;
	void handleEvent(sf::Event& event, sf::RenderTarget& target) override;
	void update() override;
	void draw(sf::RenderTarget& target) override;
};

