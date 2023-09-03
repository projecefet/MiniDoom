#ifndef SRC_HEADERS_GAME_HPP_
#define SRC_HEADERS_GAME_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>

#include "map.hpp"

class Game {
private:
	Map map;
	Background back;
	sf::RenderWindow *window;

	Player jogador;
	Saint *saint = new Saint;
	vector<Snake> cobras = { Snake(290, 144), Snake(100, 144), Snake(471, 128),
			Snake(856, 255), Snake(1243, 272), Snake(2432, 128), Snake(2815, 257), 
			Snake(3025, 257), Snake (139, 320), Snake (319, 321), Snake (628, 368) };

	int saintBulletId = 0;
	int bulletId = 0;
	std::vector<Bullet*> bullets;

	sf::SoundBuffer soundBufferShot;
	sf::Sound ShotSound;

	sf::Font font;
	sf::Text enemiesLeftText;

	void drawLifes() {
		sf::Vector2f newPositionHeart1;
		newPositionHeart1.x = jogador.shape.getPosition().x - 145;
		newPositionHeart1.y = jogador.shape.getPosition().y - 170;

		jogador.heartSprites.at(0).setScale(0.1, 0.1);
		jogador.heartSprites.at(1).setScale(0.1, 0.1);
		jogador.heartSprites.at(2).setScale(0.1, 0.1);

		jogador.heartSprites.at(0).setPosition(newPositionHeart1);
		jogador.heartSprites.at(1).setPosition(newPositionHeart1.x + 28,
				newPositionHeart1.y);
		jogador.heartSprites.at(2).setPosition(newPositionHeart1.x + 56,
				newPositionHeart1.y);

		switch (jogador.lifes) {
		case 3:
			window->draw(jogador.heartSprites.at(0));
			window->draw(jogador.heartSprites.at(1));
			window->draw(jogador.heartSprites.at(2));
			break;
		case 2:
			window->draw(jogador.heartSprites.at(0));
			window->draw(jogador.heartSprites.at(1));
			break;
		case 1:
			window->draw(jogador.heartSprites.at(0));
			break;
		default:
			break;
		}

	}
	void drawSaint(Saint *saint, Map &map, Player &player,
			sf::RenderWindow *window) {

		if (saint->checkDeath() == false) {
			saint->update(&map, &player);
			saint->render(window);
			saint->updateAnimation();
			window->draw(saint->saintSprite);
		}
	}
	void drawSnake(Snake *snake, Map &map, Player &player,
			sf::RenderWindow *window) {
		if (snake->checkDeath() == false) {
			snake->updateAnimation();
			snake->render(window);
			snake->sprite.setScale(0.1, 0.1);
			snake->sprite.setPosition(snake->shape.getPosition());
			window->draw(snake->sprite);
		}
	}
	void deleteBullets() {
		for (int i = 0; i < bullets.size(); i++) {
			if (bullets.at(i)->timer >= 200) {
				bullets.erase(bullets.begin() + i);
			}
		}
		for (int i = 0; i < saint->bullets.size(); i++) {
			if (saint->bullets.at(i).timer >= 200) {
				saint->bullets.erase(saint->bullets.begin() + i);
			}
		}
	}

	void doDamageToPlayer() {
		if (saint->checkDeath() == false) {
			jogador.receiveDamage(saint->hitbox);
		}

		for (int i = 0; i < saint->bullets.size(); i++) {
			jogador.receiveDamage(saint->bullets.at(i).hitbox);
		}
		for (int i = 0; i < cobras.size(); i++) {
			if (cobras.at(i).checkDeath() == false) {
				jogador.receiveDamage(cobras.at(i).hitbox);
			}
		}
	}

public:

	Game() :
			map("mapa.png", "info.xml"), back("resources/background.jpg",
					sf::Vector2f(1600, 1200), sf::Vector2f(-400.f, -200.f)) {
		window = new sf::RenderWindow(sf::VideoMode(800, 600),
				"Mini Doom Remake", sf::Style::Close | sf::Style::Titlebar);

		font.loadFromFile("resources/text/wesr.ttf");
		enemiesLeftText.setFont(font);
		enemiesLeftText.setCharacterSize(23);
		enemiesLeftText.setFillColor(sf::Color(139, 69, 19));
		enemiesLeftText.setPosition(100, 100);

		soundBufferShot.loadFromFile("resources/sounds/manshot.wav");
		ShotSound.setBuffer(soundBufferShot);

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

			int enemiesLeft = 12;

			window->clear();

			//background
			back.render(window, jogador.getPosition());

			//balas e suas relações com os inimigos
			for (int i = 0; i < bullets.size(); i++) {

				window->draw(bullets.at(i)->shape);
				bullets.at(i)->update();

				saint->gotShot(bullets.at(i));
				for (int j = 0; j < cobras.size(); j++) {
					cobras.at(j).gotShot(bullets.at(i));
				}
			}

			deleteBullets();

			//mapa
			map.render(window);
			//Coisas do saint
			drawSaint(saint, map, jogador, window);
			if (saint->checkDeath() == false) {
				saint->shoot(saintBulletId, ShotSound);
			} else {
				enemiesLeft--;
			}

			for (int i = 0; i < saint->bullets.size(); i++) {
				window->draw(saint->bullets.at(i).shape);
				saint->bullets.at(i).update();
			}

			//Coisas das snakes

			for (int i = 0; i < cobras.size(); i++) {
				drawSnake(&cobras.at(i), map, jogador, window);
				if (cobras.at(i).checkDeath() == true) {
					enemiesLeft--;
				}
			}

			//coisas do player
			jogador.update(window, &map);
			jogador.shoot(bullets, bulletId, ShotSound);
			doDamageToPlayer();
			//coisas das vidas
			drawLifes();

			//texto
			cout << enemiesLeft << endl;
			enemiesLeftText.setPosition(jogador.shape.getPosition().x + 50,
					jogador.shape.getPosition().y - 170);
			enemiesLeftText.setString(
					"Coisa pa mata ainda: " + std::to_string(enemiesLeft));
			window->draw(enemiesLeftText);

			window->display();
		}
	}

};

#endif
