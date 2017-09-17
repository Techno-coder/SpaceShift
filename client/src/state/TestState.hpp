#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../State.hpp"
#include "../level/TileMapTextureProvider.hpp"
#include "../level/Map.hpp"
#include "../player/Player.hpp"
#include "../resource/ResourceIDProvider.hpp"
#include "../network/NetworkClient.hpp"

class TestState : public State {
	NetworkClient networkClient;
	std::shared_ptr<TileMapTextureProvider> textureProvider;
	ResourceIDProvider playerTextureIDProvider;
	GenericResourceProvider<sf::Texture> playerTextureProvider;
	Player player;
	Map map;
	float posX = 0, posY = 0;

	sf::Clock networkClock;
	sf::Time currentTime = sf::Time::Zero;
	void handleKeyboardInput();
public:
	TestState();

	void onEnter() override;

	void handleEvent(sf::Event& event, sf::RenderTarget& target) override;
	void update() override;
	void draw(sf::RenderTarget& target) override;
};

