#ifndef SRC_HEADERS_BULLET_HPP_
#define SRC_HEADERS_BULLET_HPP_

#include "entity.hpp"
#include "map.hpp"
class Bullet: public Entity{
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
		shape.setFillColor(sf::Color::Black);
		shape.setPosition(position);
		this->id = id;
		id++;

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
		sf::Vector2f spritePosition;
		spritePosition = position;
		spritePosition.y = spritePosition.y + 2;
		shape.setPosition(spritePosition);

		timer++;

		hitbox = shape.getGlobalBounds();

	}
};

#endif
