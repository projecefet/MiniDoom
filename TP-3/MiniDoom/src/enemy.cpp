#include "headers/enemy.hpp"

Saint::Saint() { //construtor do boss final
		this->position = sf::Vector2f(1 * 200, 1 * 144);
		this->shape.setSize(sf::Vector2f(16, 16));
		this->shape.setFillColor(sf::Color::Red);
		this->shape.setPosition(this->position);
		this->hitbox = shape.getGlobalBounds();
}

Snake::Snake(int posx, int posy){ //inimigo estatico
		this->position = sf::Vector2f(1 * posx, 1 * posy);

		this->shape.setSize(sf::Vector2f(16, 16));
		this->shape.setFillColor(sf::Color::Blue);
		this->shape.setPosition(this->position);
		this->hitbox = shape.getGlobalBounds();
}

Snake::~Snake(){
}

void Saint::update(Map *map, Player *jogador) {
	if ((position.x - jogador->position.x <= 140 || distanceAllowed == true)) { //primeiro bloco
		distanceAllowed = true;
		//a diferença entre a posicao do jogador e do inimigo != 0
		if ((jogador->position.x - position.x) < -18) { //esquerda
			shape.move(-followspeed, 0.f);
			newPosition = shape.getPosition();
			position = newPosition;
		} else if ((jogador->position.x - position.x) > 18) { //direita
			shape.move(followspeed, 0.f);
			newPosition = shape.getPosition();
			position = newPosition;
		}

		hitbox = shape.getGlobalBounds();

	}
}


bool Enemy::gotShot(Bullet *&bullet) {

	int auxiliaryIncrement = 0;
	if (bullet->hitbox.intersects(hitbox)) {

		if (idBulletsHit.size() != 0) {
			for (int i = 0; i < idBulletsHit.size(); i++) {
				if (bullet->id != idBulletsHit.at(i)) {
					auxiliaryIncrement++;
				}
			}
			if (auxiliaryIncrement == idBulletsHit.size()) {
				idBulletsHit.push_back(bullet->id);
			}
		} else {
			idBulletsHit.push_back(bullet->id);
		}
	}
	return bullet->hitbox.intersects(hitbox);
}

bool Enemy::checkDeath() {
	return idBulletsHit.size() >= 10;
}

void Enemy::render(sf::RenderWindow *window) {
	window->draw(this->shape);
}


