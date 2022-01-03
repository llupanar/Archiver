#include "Game.h"
Game::Game()
{
	font.loadFromFile("fonts/font_game.ttf");
	startInitialization();
}

void Game::startInitialization()
{
	for (int i = 0; i < ALL_ELEMENTS - 1; i++) elements[i] = i + 1;
	empty_element = ALL_ELEMENTS - 1;
	elements[empty_element] = 0;
	is_end = true;
}

bool Game::checkCondition()
{
	for (int i = 0; i < ALL_ELEMENTS; i++)
	{
		if (elements[i] > 0 && elements[i] != i + 1) return false;
	}
	return true;
}


void Game::Move(int direction)
{
	int new_emptyElement = 0;
	int moveFlag = 0;
	int locationEmpty_column = empty_element % ELEMENT_COUT;
	int locationEmpty_row = empty_element / ELEMENT_COUT;
	if (direction == 0 && locationEmpty_column < (ELEMENT_COUT - 1)) {
		new_emptyElement = empty_element + 1;
		moveFlag++;
	}
	if (direction == 1 && locationEmpty_column > 0) {
		new_emptyElement = empty_element - 1;
		moveFlag++;
	}
	if (direction == 2 && locationEmpty_row < (ELEMENT_COUT - 1)) {
		new_emptyElement = empty_element + ELEMENT_COUT;
		moveFlag++;
	}
	if (direction == 3 && locationEmpty_row > 0) {
		new_emptyElement = empty_element - ELEMENT_COUT;
		moveFlag++;
	}
	if (empty_element >= 0 && moveFlag != 0)
	{
		int temp = elements[empty_element];
		elements[empty_element] = elements[new_emptyElement];
		elements[new_emptyElement] = temp;
		empty_element = new_emptyElement;
	}
	is_end = checkCondition();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Color color = sf::Color(100, 100, 128);

	sf::RectangleShape shape(sf::Vector2f(FIELD_SIZE + 28, FIELD_SIZE + 20));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Transparent);
	target.draw(shape, states);


	shape.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
	shape.setOutlineThickness(2);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color::Black);

	sf::Text text("", font, 25);

	for (unsigned int i = 0; i < ALL_ELEMENTS; i++)
	{
		shape.setOutlineColor(sf::Color::Black);
		text.setFillColor(sf::Color(30, 144, 255));
		std::string name = "(0-0)   \n" + std::to_string(elements[i]);
		text.setString(name);

		if (is_end)
		{
			shape.setOutlineColor(sf::Color::Black);
			text.setFillColor(sf::Color(255, 255, 0));
			std::string lolname = "(*-*)   \n" + std::to_string(elements[i]);
			text.setString(lolname);

		}
		else if (elements[i] == i + 1)
		{
			std::string lolname = "(*-*)   \n" + std::to_string(elements[i]);
			text.setString(lolname);
			text.setFillColor(sf::Color(255, 255, 0));
		}

		if (elements[i] > 0)
		{
			sf::Vector2f position(i % ELEMENT_COUT * CELL_SIZE + 10, i / ELEMENT_COUT * CELL_SIZE + 10);
			shape.setPosition(position);

			text.setPosition(position.x + 7, position.y + 5);
			target.draw(shape, states);
			target.draw(text, states);
		}
	}
}