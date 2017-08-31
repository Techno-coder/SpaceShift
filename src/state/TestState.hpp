#pragma once

#include "../State.hpp"
#include "../resource/TextureProvider.hpp"
#include "../Tilemap.hpp"

class TestState : public State {
	TextureProvider textureProvider;
	Tilemap tilemap;
	float posX = 0, posY = 0;
public:
	void onEnter() override;

	void handleEvent(sf::Event& event, sf::RenderTarget& target) override;
	void update() override;
	void draw(sf::RenderTarget& target) override;
};

