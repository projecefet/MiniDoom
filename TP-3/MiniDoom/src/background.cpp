#include "headers/background.hpp"

Background::Background(string path, sf::Vector2f size, sf::Vector2f startPos) {
  this->texture.loadFromFile(path);
  this->background.setSize(size);
  this->background.setPosition(startPos);
  this->background.setTexture(&this->texture);
  this->startPos = startPos;
}

Background::~Background() {}

void Background::render(sf::RenderWindow *i_window, sf::Vector2f playerPos) {
  // 2 é a velocidade do parallax, se mudar ela a velocidade fica mais rapida ou devagar
  this->background.setPosition(
      sf::Vector2f(this->startPos.x + playerPos.x / 2, this->startPos.y + playerPos.y / 2));
  i_window->draw(this->background);
}
