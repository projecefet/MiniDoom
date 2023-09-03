#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "Exemplo de Imagem SFML");
	sf::Texture imagem;
	sf::Sprite fundo;
	sf::Vector2i leituramouse;
	sf::Vector2f cordenadatual;

	imagem.loadFromFile("resources/screens/menu.png");
	fundo.setTexture(imagem);

	sf::RectangleShape mouseplay(sf::Vector2f(210, 101));
	mouseplay.setPosition(300, 340);
	mouseplay.setFillColor(sf::Color::Transparent);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed){
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				leituramouse = sf::Mouse::getPosition(window);
				cordenadatual = window.mapPixelToCoords(leituramouse);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					if (mouseplay.getGlobalBounds().contains(cordenadatual)) {
						cout << "botao pressionado" << endl;
					}
				}
			}
		}
		window.clear(sf::Color::White);
		window.draw(fundo);
		window.draw(mouseplay);
		window.display();
	}
	return 0;
}
