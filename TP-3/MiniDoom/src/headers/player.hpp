#pragma once

#include <SFML/audio.hpp>
#include "map.hpp"
#include "bullet.hpp"
#include "entity.hpp"

class Player: public Entity {
private:

	int jumpCooldown = 200;
	int jump_HoldTime = 0;
	const int max_Jump_HoldTime = 15;
	bool jumped = false;

	int shootCooldown = 0;
	int max_ShootCooldown = 40;

	sf::Texture facingRightTextures[4];
	sf::Texture facingLeftTextures[4];
	int textureIndex = 0;
	int currentFrame = 0;

	sf::Texture heartTexture;

	enum direction {
		left, right
	};
	int direction = right;

	sf::Clock playerClock;

	float velocity = 200;

	int damageReceivedCooldown = 0;
public:

	sf::Vector2f position;
	std::vector<sf::Sprite> heartSprites;
	int lifes = 3;

	Player();
	~Player();

	void move(Map *map);
	void shoot(std::vector<Bullet*> &bullets, int &id, sf::Sound& sound);
	void receiveDamage(sf::FloatRect rect);
	void jump(Map *map);
	void walkLeft(Map *map);
	void walkRight(Map *map);
	void groundColision(Map *map);
	void hitTrap(Map *map);
	void update(sf::RenderWindow *window, Map *map);
	void updateAnimation();
	void render(sf::RenderWindow *i_window);
	void reSpawn();

	sf::Vector2f getPosition();
};
