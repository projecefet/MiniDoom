#pragma once

#include "map.hpp"
#include "bullet.hpp"
#include "movable.hpp"

class Player: public Movable {
 private:

  int jumpCooldown = 200;
  int jump_HoldTime = 0;
  const int max_Jump_HoldTime = 30;
  bool jumped = false;



  sf::Clock playerClock;

  float velocity = 200;

 public:
  enum direction{
  		left,
  		right
  	};
  int direction = right;
  int shootCooldown = 0;
  sf::Vector2f position;

  Player();
  ~Player();


  void update(Map *map);
  void shoot(std::vector<Bullet*> &bullets, int &id);
  void render(sf::RenderWindow *i_window);
  void die();

  sf::Vector2f getPosition();
};
