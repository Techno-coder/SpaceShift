#pragma once

#include "../State.hpp"
#include "../tilemap/Tilemap.hpp"
#include "../tilemap/TilemapTextureProvider.hpp"

class TestState : public State {
	std::shared_ptr<TilemapTextureProvider> textureProvider = std::make_shared<TilemapTextureProvider>();
	Tilemap tilemap;
	float posX = 0, posY = 0;
public:
	void onEnter() override;

	void handleEvent(sf::Event& event, sf::RenderTarget& target) override;
	void update() override;
	void draw(sf::RenderTarget& target) override;
};

