#include "StateManager.hpp"
//#include "state/TitleScreenState.hpp"
#include "state/TestState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

const int DRAW_RATE_LIMIT = 60;
const int UPDATE_RATE = 60;

void draw(sf::RenderWindow& window, StateManager& stateManager) {
	window.clear(sf::Color::Black);
	stateManager.draw(window);
	window.display();
}

void update(sf::RenderWindow& window, StateManager& stateManager) {
	static sf::Clock clock;
	static sf::Time accumulator = sf::Time::Zero;
	const sf::Time updatesPerSecond = sf::seconds(1.f / UPDATE_RATE);
	while (accumulator > updatesPerSecond) {
		accumulator -= updatesPerSecond;
		stateManager.update();
	}
	accumulator += clock.restart();
}

void handleEvents(sf::RenderWindow& window, StateManager& stateManager) {
	sf::Event event{};
	while (window.pollEvent(event)) {
		stateManager.handleEvent(event, window);
		if (event.type == sf::Event::Closed) {
			window.close();
			return;
		}
	}
}

int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode(640, 480), "SpaceShift");
	window.setFramerateLimit(DRAW_RATE_LIMIT);

	loadAllDefaultResources();

	StateManager stateManager;
	stateManager.pushState(std::make_unique<TestState>());

	while (window.isOpen()) {
		handleEvents(window, stateManager);
		update(window, stateManager);
		draw(window, stateManager);
	}
}