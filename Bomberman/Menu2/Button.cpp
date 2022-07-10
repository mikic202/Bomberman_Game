#include "Button.h"

Button::Button(sf::Vector2f position, int size, sf::Color color, std::string text)
{
	if (!font_.loadFromFile("arial.ttf"))
	{
		throw(std::exception());
	}
	button_text_.setFont(font_);
	button_text_.setString(text);
	button_text_.setCharacterSize(size);
	button_text_.setFillColor(color);
	auto center = button_text_.getGlobalBounds().left / 2.f;
	button_text_.setOrigin({ center, button_text_.getGlobalBounds().top });
	button_text_.setPosition(position);
}

void Button::draw_to(sf::RenderWindow& window)
{
	window.draw(button_text_);
}

bool Button::is_pressed(sf::RenderWindow& window)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	return button_text_.getGlobalBounds().contains({ mouse_pos.x, mouse_pos.y});
}

