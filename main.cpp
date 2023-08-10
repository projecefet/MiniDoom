// MAIN

#include "character.hpp"

int main() {

	sf::RenderWindow window(sf::VideoMode(960, 540),
			"MARIO KART: Super Circuit 2600",
			sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	Texture mainCharacterTexture;
	if (!mainCharacterTexture.loadFromFile("assets/mainCharacter.png")) {
		cout << "Erro ao carregar textura: mainCharacterTexture.png" << endl;
	}
	Vector2f startPosition_mainCharacter(100, 100);
	Player mainCharacter(&mainCharacterTexture, startPosition_mainCharacter);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		mainCharacter.move();
		mainCharacter.tookDamage();
		mainCharacter.healed();

		window.clear();
		mainCharacter.drawPlayer(&window);
		window.display();
	}
	return 0;
}
