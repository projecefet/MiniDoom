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
	Enemy *enemy1 = new Enemy(1);
	Enemy *enemy2 = new Enemy(2);
	Enemy *enemy3 = new Enemy(3);

	int bulletId = 0;
	std::vector<Bullet*> bullets;

	void drawEnemy(Enemy *enemy, Map &map, Player &player,
			sf::RenderWindow *window) {
		if (enemy->checkDeath() == false) {
			enemy->update(&map, &player);
			enemy->render(window);
		}
	}
	void deleteBullet(int index) {
		if (bullets.at(index)->timer >= 1000
				|| (bullets.at(index)->hitbox.intersects(enemy1->hitbox)
						&& !enemy1->checkDeath())
				|| (bullets.at(index)->hitbox.intersects(enemy2->hitbox)
						&& !enemy2->checkDeath())
				|| (bullets.at(index)->hitbox.intersects(enemy3->hitbox)
						&& !enemy3->checkDeath())) {
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

				enemy1->gotShot(bullets.at(i));
				enemy2->gotShot(bullets.at(i));
				enemy3->gotShot(bullets.at(i));

				deleteBullet(i);
			}

			jogador.update(window, &map);
			jogador.shoot(bullets, bulletId);

			drawEnemy(enemy1, map, jogador, window);
			drawEnemy(enemy2, map, jogador, window);
			drawEnemy(enemy3, map, jogador, window);

			map.render(window);
			window->display();
		}
	}

};

#endif
