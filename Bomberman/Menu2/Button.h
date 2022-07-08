#ifndef Button_H
#define Button_H
#include <vector>
#include <SFML/Graphics.hpp>


class Button
{
private:
	sf::RectangleShape butto_rect_;
public:
	Button(sf::Vector2f position, sf::Vector2f size, sf::Color button_color, sf::Text text);
};


#endif // !Button_H

