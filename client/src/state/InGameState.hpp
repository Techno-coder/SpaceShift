#pragma once

#include "../State.hpp"
#include "../level/Map.hpp"
#include "../resource/StaticResourceProviders.hpp"

class InGameState : public State {
	Map currentMap{globalTileMapTextureIDs, globalTextures};
public:
	void onEnter() override;
	void handleEvent(sf::Event& event, sf::RenderTarget& target) override;
	void update() override;
	void draw(sf::RenderTarget& target) override;
};

