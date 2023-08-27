#include "headers/enemy.hpp"

Enemy::Enemy() {
	this->position = sf::Vector2f(1 * 256, 1 * 80);

	this->shape.setSize(sf::Vector2f(16, 16));
	this->shape.setFillColor(sf::Color::Blue);
	this->shape.setPosition(this->position);
	this->hitbox = shape.getGlobalBounds();
}

Enemy::~Enemy() {
}

void Enemy::update(Map *map, Player *jogador) {
	if ((position.x - jogador->position.x) <= 140 || distanceAllowed == true) {
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

		distanceAllowed = true;

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

void Enemy::render(sf::RenderWindow *i_window) {
	i_window->draw(this->shape);
}