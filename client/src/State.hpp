#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

class State {
public:
	virtual void onEnter() = 0;

	virtual void handleEvent(sf::Event& event, sf::RenderTarget& target) = 0;
	virtual void update() = 0;
	virtual void draw(sf::RenderTarget& target) = 0;
};

