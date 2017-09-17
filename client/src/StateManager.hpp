#pragma once

#include <stack>

namespace sf {
	class RenderTarget;

	class Event;
}

class State;

class StateManager {
	std::stack<std::unique_ptr<State>> states;
public:
	void pushState(std::unique_ptr<State> state);
	void changeState(std::unique_ptr<State> state);
	void popState();

	void handleEvent(sf::Event& event, sf::RenderTarget& target);
	void update();
	void draw(sf::RenderTarget& target);
};

