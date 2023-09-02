#ifndef SRC_HEADERS_ENEMY_HPP_
#define SRC_HEADERS_ENEMY_HPP_

//template<typename S>;

#include <vector>
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
    Enemy(){};
    ~Enemy(){};

	bool gotShot(Bullet *&bullet);
    void render(sf::RenderWindow *i_window);
    bool checkDeath();

    sf::Vector2f newPosition;
};

class Snake: public Enemy{ //inimigo estatico
public:
	Snake (int posx, int posy);
	~Snake();
};

class Saint: public Enemy{ //inimigo do jogo que irá seguir o player
public:
	bool distanceAllowed = false;
	float followspeed = 0.1f;

	void update(Map *map, Player * jogador);
	Saint();
	~Saint();
};

#endif
