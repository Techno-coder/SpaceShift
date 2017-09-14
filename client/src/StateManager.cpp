#include "StateManager.hpp"

#include "State.hpp"

void StateManager::pushState(std::unique_ptr<State> state) {
	states.push(std::move(state));
	states.top()->onEnter();
}

void StateManager::changeState(std::unique_ptr<State> state) {
	states.pop();
	states.push(std::move(state));
	states.top()->onEnter();
}

void StateManager::popState() {
	states.pop();
}

void StateManager::handleEvent(sf::Event& event, sf::RenderTarget& target) {
	states.top()->handleEvent(event, target);
}

void StateManager::update() {
	states.top()->update();
}

void StateManager::draw(sf::RenderTarget& target) {
	states.top()->draw(target);
}
