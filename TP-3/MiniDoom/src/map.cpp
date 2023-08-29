#include "headers/map.hpp"

using namespace sf;

// Constructors / Destructors

#include <iostream>

Map::Map(string mapName, string xmlPath) {
  /*
  - Loads map images
  - Get every pixel and maps it on mapColorFunction
  - Push the maped value to class map vector
  */

  tinyxml2::XMLDocument doc;
  doc.LoadFile(xmlPath.c_str());

  tinyxml2::XMLElement *rootNode = doc.RootElement();
  tinyxml2::XMLElement *block = rootNode->FirstChildElement("block");

  // Colocando as informações do xml no array de colisão e na matriz de tiles
  while (block) {
    Block currentBlock;

    // Informações do block
    currentBlock.color = block->FirstChildElement("color")->GetText();
    tinyxml2::XMLElement *position = block->FirstChildElement("position");

    int x = std::atoi(position->FirstChildElement("x")->GetText());
    int y = std::atoi(position->FirstChildElement("y")->GetText());

    currentBlock.position = sf::Vector2i(x, y);

    currentBlock.collision = strcmp(block->FirstChildElement("collision")->GetText(), "true");
    currentBlock.damage = strcmp(block->FirstChildElement("damage")->GetText(), "true");

    this->mapColorFunction.push_back(currentBlock);

    block = block->NextSiblingElement("block");

    // Colisão
  }

  // Lendo como o mapa é
  Image map;
  map.loadFromFile(mapName);

  Vector2u mapSize = map.getSize();

  for (unsigned int y = 0; y < mapSize.y; y++) {
    vector<Block> yAxis;
    for (unsigned int x = 0; x < mapSize.x; x++) {
      Color color = map.getPixel(x, y);

      for (unsigned int i = 0; i < this->mapColorFunction.size(); i++) {
        if (this->mapColorFunction[i].color == std::to_string(color.r) + "," +
                                                   std::to_string(color.g) + "," +
                                                   std::to_string(color.b)) {
          yAxis.push_back(this->mapColorFunction[i]);
        }
      }
    }

    this->mapTiles.push_back(yAxis);
  }
}

Map::~Map() {}

// Functions

void Map::render(RenderWindow *i_window) {
  /*
    @return void

    Draws map vector on screen
  */

  const int OFFSET = 16;

  Texture gameTexture;
  gameTexture.loadFromFile("resources/terrain-tilemap.png");

  RectangleShape square;
  square.setSize(Vector2f(OFFSET, OFFSET));

  square.setTexture(&gameTexture);

  for (unsigned int y = 0; y < this->mapTiles.size(); y++) {
    for (unsigned int x = 0; x < this->mapTiles[y].size(); x++) {
      square.setTextureRect(IntRect(OFFSET * mapTiles[y][x].position.x,
                                    OFFSET * mapTiles[y][x].position.y, OFFSET, OFFSET));
      square.setPosition(Vector2f(OFFSET * x, OFFSET * y));

      i_window->draw(square);
    }
  }
}

bool Map::doesCollide(sf::Vector2i pos) {
  if (mapTiles[pos.y][pos.x].collision) {
    return true;
  }
  return false;
}

bool Map::dealsDamage(sf::Vector2i pos) {
  if (mapTiles[pos.y][pos.x].damage) {
    return true;
  }
  return false;
}
