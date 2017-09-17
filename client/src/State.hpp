#pragma once

namespace sf {
	class Event;

	class RenderTarget;
}

class State {
public:
	virtual void onEnter() = 0;

	virtual void handleEvent(sf::Event& event, sf::RenderTarget& target) = 0;
	virtual void update() = 0;
	virtual void draw(sf::RenderTarget& target) = 0;
};

