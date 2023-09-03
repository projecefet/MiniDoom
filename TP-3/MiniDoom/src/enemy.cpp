#include "headers/enemy.hpp"
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

Snake::Snake(int posx, int posy) { //inimigo estatico
	this->position = sf::Vector2f(1 * posx, 1 * posy);

	this->shape.setSize(sf::Vector2f(16, 16));
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setPosition(this->position);
	this->hitbox = shape.getGlobalBounds();

	animationTextures[0].loadFromFile("characters/snake/snake_00.png");
	animationTextures[1].loadFromFile("characters/snake/snake_01.png");
	animationTextures[2].loadFromFile("characters/snake/snake_02.png");
	animationTextures[3].loadFromFile("characters/snake/snake_03.png");
	animationTextures[4].loadFromFile("characters/snake/snake_04.png");
	animationTextures[5].loadFromFile("characters/snake/snake_05.png");
	animationTextures[6].loadFromFile("characters/snake/snake_06.png");
	animationTextures[7].loadFromFile("characters/snake/snake_07.png");
	animationTextures[8].loadFromFile("characters/snake/snake_08.png");
	animationTextures[9].loadFromFile("characters/snake/snake_09.png");
	animationTextures[10].loadFromFile("characters/snake/snake_10.png");
	animationTextures[11].loadFromFile("characters/snake/snake_11.png");

	sprite.setTexture(animationTextures[0]);
}

void Snake::updateAnimation() {
	sprite.setTexture(animationTextures[textureIndex]);

	currentFrame++;

	if (currentFrame == 20) {
		if (textureIndex < 11) {
			textureIndex++;
		} else {
			textureIndex = 0;
		}
		currentFrame = 0;
	}
}

Snake::~Snake() {
}

Saint::Saint() { //construtor do boss final
	this->position = sf::Vector2f(1 * 5848, 1 * 256);
	this->shape.setSize(sf::Vector2f(16, 16));
	this->shape.setFillColor(sf::Color::Transparent);
	this->shape.setPosition(this->position);
	this->hitbox = shape.getGlobalBounds();

	animationTexturesRight[0].loadFromFile("characters/santocristo/walk/a.png");
	animationTexturesRight[1].loadFromFile("characters/santocristo/walk/b.png");
	animationTexturesRight[2].loadFromFile("characters/santocristo/walk/c.png");
	animationTexturesRight[3].loadFromFile("characters/santocristo/walk/d.png");

	animationTexturesLeft[0].loadFromFile("characters/santocristo/walk/0.png");
	animationTexturesLeft[1].loadFromFile("characters/santocristo/walk/1.png");
	animationTexturesLeft[2].loadFromFile("characters/santocristo/walk/2.png");
	animationTexturesLeft[3].loadFromFile("characters/santocristo/walk/3.png");

	saintSprite.setTexture(animationTexturesLeft[0]);
}
void Saint::updateAnimation() {

	if (direction == right) {
		saintSprite.setTexture(animationTexturesRight[textureIndex]);
	} else if (direction == left) {
		saintSprite.setTexture(animationTexturesLeft[textureIndex]);
	}

	saintSprite.setScale(1, 1);
	sf::Vector2f newPosition;
	newPosition.x = shape.getPosition().x - 25;
	newPosition.y = shape.getPosition().y - 38;
	saintSprite.setPosition(newPosition);

	currentFrame++;

	if (currentFrame == 30) {
		if (textureIndex < 3) {
			textureIndex++;
		} else {
			textureIndex = 0;
		}
		currentFrame = 0;
	}

}
void Saint::update(Map *map, Player *jogador) {
	if ((position.x - jogador->position.x <= 140 || distanceAllowed == true)) { //primeiro bloco
		distanceAllowed = true;
		canShoot = true;
		//a diferença entre a posicao do jogador e do inimigo != 0
		if ((jogador->position.x - position.x) < -18) { //esquerda
			shape.move(-followspeed, 0.f);
			newPosition = shape.getPosition();
			position = newPosition;
			direction = left;
		} else if ((jogador->position.x - position.x) > 18) { //direita
			shape.move(followspeed, 0.f);
			newPosition = shape.getPosition();
			position = newPosition;
			direction = right;
		}

	}
	hitbox = shape.getGlobalBounds();
}

void Saint::shoot(int &id, sf::Sound &sound) {
	burstCooldown++;
	if (burstCooldown >= max_BurstCooldown && canShoot) {
		if (shootCooldown < max_ShootCooldown) {
			shootCooldown++;
		}
		if (shootCooldown >= max_ShootCooldown) {
			Bullet newBullet(shape.getPosition(), direction, id);
			bullets.push_back(newBullet);
			shootCooldown = 0;
			if (shotsPerBurst > 0) {
				shotsPerBurst--;
			}
			if (shotsPerBurst <= 0) {
				burstCooldown = 0;
			}
			sound.play();
		}
	}
}
