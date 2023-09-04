
#ifndef SRC_HEADERS_ENTITY_HPP_
#define SRC_HEADERS_ENTITY_HPP_

#include "map.hpp"

class Entity{
public:
	sf::Vector2f position;
	sf::FloatRect hitbox;
	sf::RectangleShape shape;
	sf::Sprite sprite;
};

#endif
