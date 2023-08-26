#pragma once

#include "map.hpp"
#include "movable.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

using std::cout;
using std::endl;
using namespace sf;

class Enemy: public Movable {
private:
    //sf::Sprite enemysprite;
    //sf::Texture enemytexture;
    RectangleShape shape;
public:
	/*void draw(sf::RenderWindow * window) {
        window->draw(enemysprite);
    }

    void setScale(float scaleX, float scaleY) {
	   enemysprite.setScale(scaleX, scaleY);
   }
	*/
    Vector2f position;
    bool distanceAllowed = false;
    float followspeed = 0.1f;
    int life = 100;

    Enemy();
    ~Enemy();

	void update(Map *map, Player * jogador);
    void render(sf::RenderWindow *i_window);
    void die();

    Vector2f newPosition;
};
