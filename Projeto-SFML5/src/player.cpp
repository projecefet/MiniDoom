#include "headers/player.hpp"

Player::Player() {

	this->position = sf::Vector2f(1 * 16, 1);

	this->shape.setSize(sf::Vector2f(16, 16));
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setPosition(this->position);
	this->hitbox = shape.getGlobalBounds();

	facingRightTextures[0].loadFromFile("characters/jao/walking_gun/0.png");
	facingRightTextures[1].loadFromFile("characters/jao/walking_gun/1.png");
	facingRightTextures[2].loadFromFile("characters/jao/walking_gun/2.png");
	facingRightTextures[3].loadFromFile("characters/jao/walking_gun/3.png");

	facingLeftTextures[0].loadFromFile("characters/jao/walking_gun/a.png");
	facingLeftTextures[1].loadFromFile("characters/jao/walking_gun/b.png");
	facingLeftTextures[2].loadFromFile("characters/jao/walking_gun/c.png");
	facingLeftTextures[3].loadFromFile("characters/jao/walking_gun/d.png");

	sprite.setTexture(facingRightTextures[textureIndex]);

	heartTexture.loadFromFile("characters/jao/life.png");

	sf::Sprite heart1;
	sf::Sprite heart2;
	sf::Sprite heart3;

	heart1.setTexture(heartTexture);
	heart2.setTexture(heartTexture);
	heart3.setTexture(heartTexture);

	heartSprites.push_back(heart1);
	heartSprites.push_back(heart2);
	heartSprites.push_back(heart3);

}

Player::~Player() {

}


void Player::receiveDamage(sf::FloatRect rect) {
	damageReceivedCooldown++;
	if (hitbox.intersects(rect) && damageReceivedCooldown >= 2000) {
		lifes--;
		damageReceivedCooldown = 0;
	}
}
void Player::updateAnimation() {

	if (direction == right) {
		sprite.setTexture(facingRightTextures[textureIndex]);
	} else if (direction == left) {
		sprite.setTexture(facingLeftTextures[textureIndex]);
	}

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

void Player::hitTrap(Map *map) {
	if (!map->dealsDamage(
			sf::Vector2i(this->position.x / 16, this->position.y / 16))) {
		this->reSpawn();
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

void Player::shoot(std::vector<Bullet*> &bullets, int &id, sf::Sound &sound) {
	if (shootCooldown < max_ShootCooldown) {
		shootCooldown++;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
			&& shootCooldown >= max_ShootCooldown) {
		Bullet *newBullet = new Bullet(position, direction, id);
		bullets.push_back(newBullet);
		shootCooldown = 0;
		sound.play();
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

void Player::reSpawn() {
	this->position = sf::Vector2f(2 * 16, 3 * 16);
}

void Player::update(sf::RenderWindow *window, Map *map) {
	move(map);
	hitTrap(map);
	updateAnimation();
	render(window);
	hitbox = shape.getGlobalBounds();
}

sf::Vector2f Player::getPosition() {
	return this->shape.getPosition();
}
