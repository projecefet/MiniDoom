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
    //sf::Sprite enemysprite;
    //sf::Texture enemytexture;

	std::vector<int> idBulletsHit;

public:
	/*void draw(sf::RenderWindow * window) {
        window->draw(enemysprite);
    }

    void setScale(float scaleX, float scaleY) {
	   enemysprite.setScale(scaleX, scaleY);
   }
	*/

    bool distanceAllowed = false;
    float followspeed = 0.1f;
    int life = 100;

    Enemy();
    ~Enemy();

	void update(Map *map, Player * jogador);
	bool gotShot(Bullet *&bullet);
    void render(sf::RenderWindow *i_window);
    bool checkDeath();

    sf::Vector2f newPosition;
};

#endif
