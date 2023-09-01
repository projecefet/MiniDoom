#pragma once

#include "map.hpp"
#include "bullet.hpp"
#include "movable.hpp"

class Player: public Movable {
private:

	int jumpCooldown = 200;
	int jump_HoldTime = 0;
	const int max_Jump_HoldTime = 15;
	bool jumped = false;

	int shootCooldown = 0;
	int max_ShootCooldown = 40;

	sf::Texture walkingTextures[4];
	int textureIndex = 0;
	int currentFrame = 0;

	enum direction {
		left, right
	};
	int direction = right;

	sf::Clock playerClock;

	float velocity = 200;

public:

	sf::Vector2f position;

	Player();
	~Player();

	void move(Map *map);
	void shoot(std::vector<Bullet*> &bullets, int &id);
	void jump(Map *map);
	void walkLeft(Map *map);
	void walkRight(Map *map);
	void groundColision(Map *map);
	void died(Map *map);
	void update(sf::RenderWindow *window, Map *map);
	void updateAnimation();
	void render(sf::RenderWindow *i_window);
	void die();

	sf::Vector2f getPosition();
};
