#include "headers/player.hpp"

Player::Player() {

	this->position = sf::Vector2f(1 * 16, 1);

	this->shape.setSize(sf::Vector2f(16, 16));
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setPosition(this->position);

	walkingTextures[0].loadFromFile("characters/jao/walking_gun/0.png");
	walkingTextures[1].loadFromFile("characters/jao/walking_gun/1.png");
	walkingTextures[2].loadFromFile("characters/jao/walking_gun/2.png");
	walkingTextures[3].loadFromFile("characters/jao/walking_gun/3.png");

	sprite.setTexture(walkingTextures[textureIndex]);

}

Player::~Player() {

}
void Player::updateAnimation() {

	sprite.setTexture(walkingTextures[textureIndex]);
//	cout << textureIndex << " - textureIndex" << endl;
	currentFrame++;
	if (currentFrame == 15) {
		if (textureIndex < 3) {
			textureIndex++;
		} else {
			textureIndex = 0;
		}
		currentFrame = 0;
	}
}
void Player::groundColision(Map *map) {
	if (map->doesCollide(
			sf::Vector2i(this->position.x / 16, this->position.y / 16 + 1))) {
		this->position.y += velocity
				* this->playerClock.getElapsedTime().asSeconds();
	}
}
void Player::jump(Map *map) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
			&& (jumpCooldown >= 50 || jumped == true)) {
		if (jumpCooldown >= 50) {
			jumpCooldown = 0;
		}
		if (jump_HoldTime <= max_Jump_HoldTime
				&& map->doesCollide(
						sf::Vector2i(this->position.x / 16,
								this->position.y / 16))) {

			this->position.y = position.y - 7;

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
}

void Player::walkLeft(Map *map) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)
			&& map->doesCollide(
					sf::Vector2i(this->position.x / 16 - 1,
							this->position.y / 16))) {
		this->position.x -= velocity
				* this->playerClock.getElapsedTime().asSeconds();
		direction = left;
	}
}

void Player::walkRight(Map *map) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)
			&& map->doesCollide(
					sf::Vector2i(this->position.x / 16 + 1,
							this->position.y / 16))) {
		this->position.x += velocity
				* this->playerClock.getElapsedTime().asSeconds();
		direction = right;
	}
}

void Player::died(Map *map) {
	if (!map->dealsDamage(
			sf::Vector2i(this->position.x / 16, this->position.y / 16))) {
		this->die();
	}
}
void Player::move(Map *map) {

	// Colisão da cabeça pra pulo
	if (map->doesCollide(
			sf::Vector2i(this->position.x / 16, this->position.y / 16))) {
	}
	groundColision(map);
	walkRight(map);
	walkLeft(map);
	jump(map);

// Mudando a posição
	this->shape.setPosition(this->position);
	this->playerClock.restart();

}

void Player::shoot(std::vector<Bullet*> &bullets, int &id) {
	if (shootCooldown < max_ShootCooldown) {
		shootCooldown++;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
			&& shootCooldown >= max_ShootCooldown) {
		Bullet *newBullet = new Bullet(position, direction, id);
		bullets.push_back(newBullet);
		shootCooldown = 0;
	}
}

void Player::render(sf::RenderWindow *window) {
// A view ta de tamanho diferente da janela pro jogo ficar em um zoom, se quiser só mudar
	window->draw(this->shape);
	sf::Vector2f spritePosition;
	spritePosition = shape.getPosition();
	spritePosition.y = spritePosition.y - 28;
	spritePosition.x = spritePosition.x - 10;
	sprite.setPosition(spritePosition);
	window->draw(sprite);
	window->setView(
			sf::View(sf::Vector2f(this->position.x + 50, this->position.y - 25),
					sf::Vector2f(400, 300)));
} // 400/300

void Player::die() {
	this->position = sf::Vector2f(2 * 16, 3 * 16);
}

void Player::update(sf::RenderWindow *window, Map *map) {
	move(map);
	died(map);
	updateAnimation();
	render(window);
}

sf::Vector2f Player::getPosition() {
	return this->shape.getPosition();
}
