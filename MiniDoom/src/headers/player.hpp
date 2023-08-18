#pragma once

#include <SFML/Graphics.hpp>

#include "map.hpp"

class Player {
 private:
  sf::Vector2f pos;
  sf::RectangleShape rect;

  sf::Clock playerClock;

  int velocity = 200;

 public:
  Player();
  ~Player();

  void update(Map *map);
  void render(sf::RenderWindow *i_window);
  void die();

  sf::Vector2f getPosition();
};
