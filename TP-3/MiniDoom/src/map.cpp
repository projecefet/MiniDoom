#include <SFML/Graphics.hpp>

#include "headers/background.hpp"
#include "headers/map.hpp"
#include "headers/player.hpp"
#include "headers/bullet.hpp"

int main() {
	sf::RenderWindow *window;
	sf::VideoMode videoMode(800, 600);
	window = new sf::RenderWindow(videoMode, "Joguinho legal",
			sf::Style::Close | sf::Style::Titlebar);

	Player jogador;
	Map mapa("maps/mapa.png", "info.xml");
	Background back("resources/background.jpg", sf::Vector2f(1600, 1200),
			sf::Vector2f(-400.f, -200.f));
	std::vector<Bullet*> bullets;

	while (window->isOpen()) {
		sf::Event ev;
		while (window->pollEvent(ev)) {
			if (ev.type == sf::Event::Closed
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
				window->close();
			}
		}

		window->clear();

		back.render(window, jogador.getPosition());

		jogador.update(&mapa);
		jogador.shoot(bullets);
		jogador.render(window);

		for (int i = 0; i < bullets.size(); i++) {

			window->draw(bullets.at(i)->shape);
			bullets.at(i)->update();

			if (bullets.at(i)->timer >= 1000) {
				bullets.erase(bullets.begin() + i);
			}
		}

		mapa.render(window);

		window->display();
	}

	return 0;
}
