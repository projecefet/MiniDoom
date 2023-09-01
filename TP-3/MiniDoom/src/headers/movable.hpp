
#ifndef SRC_HEADERS_MOVABLE_HPP_
#define SRC_HEADERS_MOVABLE_HPP_

#include "map.hpp"

class Movable{
public:
	sf::Vector2f position;
	sf::FloatRect hitbox;
	sf::RectangleShape shape;
	sf::Sprite sprite;
};

#endif
