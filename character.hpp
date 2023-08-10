#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include "header.hpp"

class Character {
protected:
	Vector2f position;
	Sprite sprite;
	float healthPoints;
};

class Player: public Character {
public:

	Player(Texture *texture, Vector2f startPosition) {
		sprite.setTexture(*texture);
		sprite.setScale(0.05, 0.05);
		position = startPosition;
		sprite.setPosition(position);
		healthPoints = 100;
		cout << "Criação do Player realizada com sucesso" << endl;
	}

	void move() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			position.y = position.y - 2;
			sprite.setPosition(position);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			position.y = position.y + 2;
			sprite.setPosition(position);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			position.x = position.x + 2;
			sprite.setPosition(position);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			position.x = position.x - 2;
			sprite.setPosition(position);
		}
	}

	void tookDamage() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
			healthPoints = healthPoints - 0.5;
			cout << "ARGH - Damage taken" << endl;
			cout << "HP: " << healthPoints << endl << endl;
		}
	}

	void healed() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
			healthPoints = healthPoints + 25;

				cout << "OH YEAHH - Got healed" << endl;
				cout << "HP: " << healthPoints << endl << endl;
			}
		}

	void drawPlayer(sf::RenderWindow *window) {
		window->draw(sprite);
	}
};

#endif
