#ifndef SRC_HEADERS_BULLET_HPP_
#define SRC_HEADERS_BULLET_HPP_

#include "map.hpp"
#include "movable.hpp"
class Bullet: public Movable{
private:
	sf::Vector2f position;
	sf::FloatRect hitbox;
	enum direction{
	  		left,
	  		right
	  	};
	int direction;

public:

	sf::RectangleShape shape;
	int timer = 0;

	Bullet(sf::Vector2f startPosition, const int direction) {
		position = startPosition;
		shape.setSize(sf::Vector2f(10, 2));
		shape.setFillColor(sf::Color::Blue);
		shape.setPosition(position);

		hitbox = shape.getGlobalBounds();
		this->direction = direction;
	}
	~Bullet(){

	}

	void update() {
		if(direction == right){
			position.x = position.x + 0.8;
		}
		else if(direction == left){
			position.x = position.x - 0.8;
		}
		shape.setPosition(position);

		timer++;

	}
	/*
	void draw(sf::RenderWindow *window, std::vector<Bullet> bullets){
		for(int i = 0; i < bullets.size(); i++){
			window->draw(bullets.at(i).shape);
		}

	}
	*/
};
#endif
