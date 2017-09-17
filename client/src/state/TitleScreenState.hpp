#pragma once

#include "../State.hpp"
#include "../gui/Button.hpp"

class TitleScreenState : public State {
	struct Buttons {
		Button login;

		void onMouseMove(int xPosition, int yPosition) {
			login.onMouseMove(xPosition, yPosition);
		}

		void onMouseClick() {
			login.onMouseClick();
		}
	} buttons;

public:
	TitleScreenState();
	void onEnter() override;

	void handleEvent(sf::Event& event, sf::RenderTarget& target) override;
	void update() override;
	void draw(sf::RenderTarget& target) override;
};
