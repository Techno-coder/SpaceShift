#pragma once

#include "../State.hpp"
#include "../tilemap/TileMap.hpp"
#include "../tilemap/TileMapTextureProvider.hpp"
#include "../level/Map.hpp"
#include "../player/Player.hpp"
#include "../resource/TextureResourceIDProvider.hpp"

class TestState : public State {
	std::shared_ptr<TileMapTextureProvider> textureProvider = std::make_shared<TileMapTextureProvider>();
	TextureResourceIDProvider playerTextureIDProvider;
	GenericTextureProvider playerTextureProvider;
	Player player;
	Map map;
	TileMap tileMap;
	float posX = 0, posY = 0;

	void handleKeyboardInput();
public:
	void onEnter() override;

	void handleEvent(sf::Event& event, sf::RenderTarget& target) override;
	void update() override;
	void draw(sf::RenderTarget& target) override;
};

