#pragma once

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <SFML/Graphics.hpp>
#include <cstring>

#include "../tinyxml2.h"

struct Block {
  string color;
  sf::Vector2i position;
  bool collision;
  bool damage;
};

class Map {
 private:
  vector<vector<Block>> mapTiles;

 public:
  vector<Block> mapColorFunction;

  // Constructor / Destructor
  Map(string mapName, string xmlPath);
  ~Map();

  // Functions
  void render(sf::RenderWindow *i_window);

  // Collision functions
  bool doesCollide(sf::Vector2i pos);
  bool dealsDamage(sf::Vector2i pos);
};
