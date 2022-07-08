#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color button_color, sf::Text text)
{
	butto_rect_.setPosition(position);
	butto_rect_.setSize(size);
	butto_rect_.setFillColor(button_color);
	
}
