#ifndef SRC_HEADERS_ENEMY_HPP_
#define SRC_HEADERS_ENEMY_HPP_

#include "map.hpp"
#include "movable.hpp"
#include "player.hpp"
#include "bullet.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using std::cout;
using std::endl;

class Enemy: public Movable {
private:
	std::vector<int> idBulletsHit;
public:
    bool distanceAllowed = false;
    float followspeed = 0.1f;
    int enemyId;

    Enemy(int enemyId);
    ~Enemy();

	void update(Map *map, Player * jogador);
	bool gotShot(Bullet *&bullet);
    void render(sf::RenderWindow *i_window);
    bool checkDeath();

    sf::Vector2f newPosition;
};

#endif
