#include "InGameState.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

void InGameState::onEnter() {

}

void InGameState::handleEvent(sf::Event& event, sf::RenderTarget& target) {

}

void InGameState::update() {

}

void InGameState::draw(sf::RenderTarget& target) {
	target.draw(currentMap);
}
