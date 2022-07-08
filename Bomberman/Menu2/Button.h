#ifndef Button_H
#define Button_H
#include <vector>
#include <SFML/Graphics.hpp>


class Button
{
private:
	sf::RectangleShape butto_rect_;
	sf::Text button_text_;
public:
	Button(sf::Vector2f position, sf::Vector2f size, sf::Color button_color, sf::Text text);
	void draw_to(sf::RenderWindow& window);
	bool is_pressed(sf::RenderWindow& window);
};


#endif // !Button_H

