#ifndef SRC_HEADERS_BULLET_HPP_
#define SRC_HEADERS_BULLET_HPP_

#include "map.hpp"
#include "movable.hpp"
class Bullet: public Movable{
private:

	enum direction{
	  		left,
	  		right
	  	};
	int direction;

public:
	int id;
	int timer = 0;


	Bullet(sf::Vector2f startPosition, const int direction, int &id) {
		position = startPosition;
		shape.setSize(sf::Vector2f(10, 2));
		shape.setFillColor(sf::Color::Red);
		shape.setPosition(position);
		this->id = id;
		id++;


		cout <<"id: " << id << endl;
		hitbox = shape.getGlobalBounds();
		this->direction = direction;
	}
	~Bullet(){

	}

	void update() {
		if(direction == right){
			position.x = position.x + 1.3;
		}
		else if(direction == left){
			position.x = position.x - 1.3;
		}
		shape.setPosition(position);

		timer++;

		hitbox = shape.getGlobalBounds();
	}
};

#endif
