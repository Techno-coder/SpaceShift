#include "TitleScreenState.hpp"
#include "../resource/GenericResourceProvider.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

void TitleScreenState::onEnter() {
}

void TitleScreenState::handleEvent(sf::Event& event, sf::RenderTarget& target) {
	switch (event.type) {
		case sf::Event::MouseMoved:
			buttons.onMouseMove(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Button::Left) buttons.onMouseClick();
			break;
		default:
			break;
	}
}

void TitleScreenState::update() {

}

void TitleScreenState::draw(sf::RenderTarget& target) {
	buttons.draw(target);
}

TitleScreenState::TitleScreenState() {
}

TitleScreenState::Buttons::Buttons() {
	login.setText("Login");
}

void TitleScreenState::Buttons::onMouseMove(int xPosition, int yPosition) {
	login.onMouseMove(xPosition, yPosition);
}

void TitleScreenState::Buttons::onMouseClick() {
	login.onMouseClick();
}

void TitleScreenState::Buttons::draw(sf::RenderTarget& target) {
	target.draw(login);
}
