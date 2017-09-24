#pragma once

#include "../State.hpp"
#include "../level/Map.hpp"
#include "../player/Player.hpp"
#include "../resource/ResourceIDProvider.hpp"
#include "../network/NetworkClient.hpp"
#include "../resource/GenericResourceProvider.hpp"
#include "../resource/StaticResourceProviders.hpp"
#include <utility/Constants.hpp>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
class TestState : public State {
	NetworkClient networkClient;
	ResourceIDProvider<std::string> playerTextureIDProvider;
	GenericResourceProvider<sf::Texture> playerTextureProvider;
	Player player;
	Map map{globalTileMapTextureIDs, globalTextures};
	float posX = 0, posY = 0;

	sf::Clock networkClock;
	sf::Time currentTime = sf::Time::Zero;
	bool isInFocus = false;

	std::map<PlayerID, sf::RectangleShape> multiplayerSprites;
	void handleKeyboardInput();
public:
	void onEnter() override;

	void handleEvent(sf::Event& event, sf::RenderTarget& target) override;
	void update() override;
	void draw(sf::RenderTarget& target) override;
};

