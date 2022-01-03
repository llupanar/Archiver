#include "gameInterface.h"

int gameInterface(sf::RenderWindow& window)
{
	window.clear();
	window.clear(sf::Color::Black);
	sf::Font font;
	font.loadFromFile("fonts/font_gameMenu.otf");
	sf::Text text(  L"[S]\nStart\n\n[Esc]\nExit ", font, 20);
	text.setPosition(570, 40.f);
	Game game;
	game.setPosition(50.f, 50.f);

	sf::Event event;
	int move_counter = 0;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) return 0;
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) return 0;
				if (event.key.code == sf::Keyboard::Left) game.Move(0);
				if (event.key.code == sf::Keyboard::Right) game.Move(1);
				if (event.key.code == sf::Keyboard::Up) game.Move(2);
				if (event.key.code == sf::Keyboard::Down) game.Move(3);
				if (event.key.code == sf::Keyboard::S)
				{
					game.startInitialization();
					move_counter = 100;
				}
			}
		}

		if (move_counter-- > 0) game.Move(rand() % 4);

		window.clear();
		window.draw(game);
		window.draw(text);
		window.display();
	}
	return 0;
}
