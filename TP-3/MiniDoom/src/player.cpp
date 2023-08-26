#include "headers/player.hpp"

Player::Player() {

	this->position = sf::Vector2f(1 * 16, 1 * 16);

	this->shape.setSize(sf::Vector2f(16, 16));
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setPosition(this->position);
}

Player::~Player() {
}

void Player::update(Map *map) {

	// Colisão da cabeça pra pulo
	if (map->doesCollide(sf::Vector2i(this->position.x / 16, this->position.y / 16))) {
	}

	// Left - Right collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
			&& map->doesCollide(
					sf::Vector2i(this->position.x / 16 + 1, this->position.y / 16))) {
		this->position.x += velocity
				* this->playerClock.getElapsedTime().asSeconds();
		direction = right;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
			&& map->doesCollide(
					sf::Vector2i(this->position.x / 16 - 1, this->position.y / 16))) {
		this->position.x -= velocity
				* this->playerClock.getElapsedTime().asSeconds();
		direction = left;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
			&& (jumpCooldown >= 200 || jumped == true)) {
		if (jumpCooldown >= 200) {
			jumpCooldown = 0;
		}
		if (jump_HoldTime <= max_Jump_HoldTime
				&& map->doesCollide(
						sf::Vector2i(this->position.x / 16, this->position.y / 16 - 1))) {

			this->position.y = position.y - 2;

			if (jump_HoldTime <= max_Jump_HoldTime) {
				jumped = true;
			}
			jump_HoldTime++;
		}
	} else {
		jump_HoldTime = 0;
		jumpCooldown++;
		jumped = false;
	}

// Ground collision
	if (map->doesCollide(
			sf::Vector2i(this->position.x / 16, this->position.y / 16 + 1))) {
		this->position.y += velocity
				* this->playerClock.getElapsedTime().asSeconds();
	}

// Procurando armadilhas
	if (!map->dealsDamage(sf::Vector2i(this->position.x / 16, this->position.y / 16))) {
		this->die();
	}

// Mudando a posição
	this->shape.setPosition(this->position);
	this->playerClock.restart();

// diminuindo o tempo de recarga do tiro
	if (shootCooldown < 100) {
		shootCooldown++;
	}

}

void Player::shoot(std::vector<Bullet*> &bullets) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootCooldown >= 100) {
		Bullet *newBullet = new Bullet(position, direction);
		bullets.push_back(newBullet);
		shootCooldown = 0;
	}
}

void Player::render(sf::RenderWindow *i_window) {
// A view ta de tamanho diferente da janela pro jogo ficar em um zoom, se quiser só mudar
	i_window->draw(this->shape);
	i_window->setView(
			sf::View(sf::Vector2f(this->position.x + 50, this->position.y - 25),
					sf::Vector2f(400, 300)));
} // 400/300

void Player::die() {
	this->position = sf::Vector2f(2 * 16, 3 * 16);
}

sf::Vector2f Player::getPosition() {
	return this->shape.getPosition();
}
