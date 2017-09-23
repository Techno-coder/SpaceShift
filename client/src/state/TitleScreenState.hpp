#pragma once

#include "../State.hpp"
#include "../gui/Button.hpp"

class TitleScreenState : public State {
	struct Buttons {
		Button login;

		Buttons();
		void onMouseMove(int xPosition, int yPosition);
		void onMouseClick();
		void draw(sf::RenderTarget& target);
	} buttons;

public:
	void onEnter() override;

	void handleEvent(sf::Event& event, sf::RenderTarget& target) override;
	void update() override;
	void draw(sf::RenderTarget& target) override;
};
