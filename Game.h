#pragma once
#include <SFML/Graphics.hpp>
const int ELEMENT_COUT = 6;
const int ALL_ELEMENTS = ELEMENT_COUT * ELEMENT_COUT;
const int FIELD_SIZE = 450;
const int CELL_SIZE = 75;


class Game : public sf::Drawable, public sf::Transformable
{
protected:
	int elements[ALL_ELEMENTS];
	int empty_element;
	bool is_end;
	sf::Font font;
public:
	Game();
	void startInitialization();
	bool checkCondition();
	void Move(int direction);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
