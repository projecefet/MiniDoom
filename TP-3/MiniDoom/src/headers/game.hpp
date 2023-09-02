#ifndef SRC_HEADERS_GAME_HPP_
#define SRC_HEADERS_GAME_HPP_

#include <SFML/Graphics.hpp>

#include "map.hpp"


class Game {
private:
	Map map;
	Background back;
	sf::RenderWindow *window;

	Player jogador;
	Saint *saint = new Saint;
	Snake *snake = new Snake(290, 144);

	vector <Snake> cobras = {
			Snake(290, 144), Snake (100, 144), Snake (471, 128), Snake (856, 255), Snake(1243, 272),
			Snake (2432, 128), Snake (2815, 257), Snake (3025, 257)
	};


	int bulletId = 0;
	std::vector<Bullet*> bullets;

	void drawSaint(Saint *saint, Map &map, Player &player,
			sf::RenderWindow *window) {
		if (saint->checkDeath() == false) {
			saint->update(&map, &player);
			saint->render(window);
		}
	}
	void drawSnake(Snake *snake, Map &map, Player &player,
			sf::RenderWindow *window) {
		if (snake->checkDeath() == false) {
			snake->render(window);
		}
	}
	void deleteBullet(int index) {
		if (bullets.at(index)->timer >= 1000 || (bullets.at(index)->hitbox.intersects(saint->hitbox) && !saint->checkDeath())
				|| (bullets.at(index)->hitbox.intersects(snake->hitbox) && !snake->checkDeath())) {
			bullets.erase(bullets.begin() + index);
		}


	}


public:

	Game() :
			map("maps/mapa.png", "info.xml"), back("resources/background.jpg",
					sf::Vector2f(1600, 1200), sf::Vector2f(-400.f, -200.f)) {
		window = new sf::RenderWindow(sf::VideoMode(800, 600),
				"Mini Doom Remake", sf::Style::Close | sf::Style::Titlebar);
	}

	void run() {
		window->setFramerateLimit(10000);
		while (window->isOpen()) {
			sf::Event ev;
			while (window->pollEvent(ev)) {
				if (ev.type == sf::Event::Closed
						|| sf::Keyboard::isKeyPressed(
								sf::Keyboard::Key::Escape)) {
					window->close();
				}
			}

			window->clear();

			back.render(window, jogador.getPosition());

			for (int i = 0; i < bullets.size(); i++) {

				window->draw(bullets.at(i)->shape);
				bullets.at(i)->update();

				saint->gotShot(bullets.at(i));
				snake->gotShot(bullets.at(i));

				deleteBullet(i);
			}

			jogador.update(window, &map);
			jogador.shoot(bullets, bulletId);

			drawSaint(saint, map, jogador, window);
			for (int i = 0; i < cobras.size(); i++){
				window->draw(cobras.at(i).shape);
			}



			map.render(window);
			window->display();
		}
	}

};

#endif
