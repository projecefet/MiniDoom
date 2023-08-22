#include "headers/player.hpp"

Player::Player() {

	this->pos = sf::Vector2f(1 * 16, 1 * 16);

	this->rect.setSize(sf::Vector2f(16, 16));
	this->rect.setFillColor(sf::Color::Red);
	this->rect.setPosition(this->pos);
}

Player::~Player() {
}

void Player::update(Map *map) {

	// Colisão da cabeça pra pulo
	if (map->doesCollide(
			sf::Vector2i(this->pos.x / 16, this->pos.y / 16 ))) {
	}

	// Left - Right collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
			&& map->doesCollide(
					sf::Vector2i(this->pos.x / 16 + 1, this->pos.y / 16))) {
		this->pos.x += velocity
				* this->playerClock.getElapsedTime().asSeconds();
		std::cout << this->playerClock.getElapsedTime().asSeconds()
				<< std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
			&& map->doesCollide(
					sf::Vector2i(this->pos.x / 16 - 1, this->pos.y / 16))) {
		this->pos.x -= velocity
				* this->playerClock.getElapsedTime().asSeconds();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
			&& jump_HoldTime <= max_Jump_HoldTime && jumpCooldown >= 200
			&& map->doesCollide(
					sf::Vector2i(this->pos.x / 16, this->pos.y / 16 - 1))) {
		this->pos.y = pos.y - 2;

		if (jump_HoldTime == max_Jump_HoldTime) {
			jumpCooldown = 0;
		}
		jump_HoldTime++;

	} else {
		jump_HoldTime = 0;
		jumpCooldown++;
	}

	// Ground collision
	if (map->doesCollide(
			sf::Vector2i(this->pos.x / 16, this->pos.y / 16 + 1))) {
		this->pos.y += velocity
				* this->playerClock.getElapsedTime().asSeconds();
	}

	// Procurando armadilhas
	if (!map->dealsDamage(sf::Vector2i(this->pos.x / 16, this->pos.y / 16))) {
		this->die();
	}

	// Mudando a posição
	this->rect.setPosition(this->pos);
	this->playerClock.restart();
}

void Player::render(sf::RenderWindow *i_window) {
	// A view ta de tamanho diferente da janela pro jogo ficar em um zoom, se quiser só mudar
	i_window->draw(this->rect);
	i_window->setView(
			sf::View(sf::Vector2f(this->pos.x + 50, this->pos.y - 25),
					sf::Vector2f(400, 300)));
} // 400/300

void Player::die() {
	this->pos = sf::Vector2f(2 * 16, 3 * 16);
}

sf::Vector2f Player::getPosition() {
	return this->rect.getPosition();
}
