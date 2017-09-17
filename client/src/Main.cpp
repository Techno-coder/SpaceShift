#include "StateManager.hpp"
#include "state/TestState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

int main() {
	StateManager stateManager;
	stateManager.pushState(std::make_unique<TestState>());

	sf::RenderWindow window;
	window.create(sf::VideoMode(640, 480), "SpaceShift");
	window.setFramerateLimit(60);

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);
	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			stateManager.handleEvent(event, window);
			if (event.type == sf::Event::Closed) {
				window.close();
				return 0;
			}
		}
		while (accumulator > ups) {
			accumulator -= ups;
			stateManager.update();
		}

		window.clear(sf::Color::Black);
		stateManager.draw(window);
		window.display();

		accumulator += clock.restart();
	}
}