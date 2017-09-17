#include "TitleScreenState.hpp"

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

}

TitleScreenState::TitleScreenState() {
	buttons.login.setText("Login");
}
