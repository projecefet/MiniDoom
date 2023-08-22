#pragma once

#include "map.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using std::cout;
using std::endl;

class Player {
 private:
  sf::Vector2f pos;
  sf::RectangleShape rect;

  int jumpCooldown = 200;
  int jump_HoldTime = 0;
  const int max_Jump_HoldTime = 30;

  sf::Clock playerClock;

  float velocity = 200;

 public:
  Player();
  ~Player();


  void update(Map *map);
  void render(sf::RenderWindow *i_window);
  void die();

  sf::Vector2f getPosition();
};
