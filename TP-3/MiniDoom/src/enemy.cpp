#include "headers/enemy.hpp"


Enemy::Enemy(){
	this->position = Vector2f(1 * 256, 1 * 80);

	this->shape.setSize(sf::Vector2f(16, 16));
	this->shape.setFillColor(sf::Color::Blue);
	this->shape.setPosition(this->position);
}

Enemy::~Enemy(){
}

void Enemy::update(Map *map, Player * jogador){
	if ((position.x - jogador->position.x) <= 140 || distanceAllowed == true){
		distanceAllowed = true;
		//a diferença entre a posicao do jogador e do inimigo != 0
		if((jogador->position.x - position.x) < -18){ //esquerda
			shape.move(-followspeed, 0.f);
			newPosition = shape.getPosition();
			position = newPosition;
		}
		else if ((jogador->position.x - position.x) > 18){ //direita
			shape.move(followspeed, 0.f);
			newPosition = shape.getPosition();
			position = newPosition;
		}

		distanceAllowed = true;
		cout << "pos Player: " << jogador->position.x << endl;
		cout << "pos Inimigo: " << newPosition.x << endl;
		cout << "pos Inimigo: " << newPosition.y << endl;

	}
}

void Enemy::die() {
	this->position = sf::Vector2f(2 * 16, 3 * 16);
}

void Enemy::render(sf::RenderWindow *i_window) {
	i_window->draw(this->shape);
}
