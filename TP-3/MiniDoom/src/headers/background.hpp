#ifndef SRC_HEADERS_BACKGROUND_HPP_
#define SRC_HEADERS_BACKGOURND_HPP_

#include <string>
using std::string;

#include <SFML/Graphics.hpp>

class Background {
 private:
  sf::Texture texture;
  sf::RectangleShape background;
  sf::Vector2f startPos;


 public:

  Background(string path, sf::Vector2f size, sf::Vector2f startPos);
  ~Background();

  void render(sf::RenderWindow *i_window, sf::Vector2f playerPos);
};

#endif
