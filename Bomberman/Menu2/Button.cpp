#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color button_color, sf::Text text)
{
	butto_rect_.setPosition(position);
	butto_rect_.setSize(size);
	butto_rect_.setFillColor(button_color);
	button_text_ = text;
}

void Button::draw_to(sf::RenderWindow& window)
{
	window.draw(butto_rect_);
	window.draw(button_text_);
}

bool Button::is_pressed(sf::RenderWindow& window)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	return butto_rect_.getGlobalBounds().contains({ mouse_pos.x, mouse_pos.y});
}


