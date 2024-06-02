#include <iostream>
#include "Population.h"

int main() {
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	sf::RenderWindow window(sf::VideoMode(600, 600), "NEAT_Flappy");
	float timer = 0.f;

	Population population;

	while (window.isOpen()) {
		Tools::restartClock();
		timer += Tools::GetTimeDelta();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		population.update();

		window.clear(sf::Color::Black);

		population.draw(window);

		window.display();
	}
}
