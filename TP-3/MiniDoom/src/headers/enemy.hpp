#ifndef SRC_HEADERS_ENEMY_HPP_
#define SRC_HEADERS_ENEMY_HPP_

//template<typename S>;

#include <vector>
#include "map.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "entity.hpp"

using std::cout;
using std::endl;

class Enemy: public Entity {
private:
	std::vector<int> idBulletsHit;
public:
	Enemy() {
	}
	;
	~Enemy() {
	}
	;

	int textureIndex = 0;
	int currentFrame = 0;

	bool gotShot(Bullet *&bullet);
	void render(sf::RenderWindow *i_window);
	bool checkDeath();

	sf::Vector2f newPosition;
};

class Snake: public Enemy { //inimigo estatico
public:
	Snake(int posx, int posy);
	~Snake();
	void updateAnimation();

private:
	sf::Texture animationTextures[12];
};

class Saint: public Enemy { //inimigo do jogo que irá seguir o player
public:
	bool distanceAllowed = false;
	float followspeed = 0.2f;

	sf::Texture animationTexturesRight[4];
	sf::Texture animationTexturesLeft[4];

	sf::Sprite saintSprite;

	std::vector<Bullet> bullets;
	int shootCooldown = 0;
	int max_ShootCooldown = 100;
	int burstCooldown = 0;
	int max_BurstCooldown = 150;
	int shotsPerBurst = 3;
	bool canShoot = false;

	enum direction {
		left, right
	};
	int direction = left;

	void update(Map *map, Player *jogador);
	void updateAnimation();
	void shoot(int &id, sf::Sound &sound);
	Saint();
	~Saint();
};

#endif
