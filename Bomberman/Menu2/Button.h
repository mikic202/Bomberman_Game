#ifndef Button_H
#define Button_H
#include <vector>
#include <SFML/Graphics.hpp>


class Button
{
private:
	sf::Font font_;
	sf::Text button_text_;
public:
	Button(sf::Vector2f position, int size, sf::Color color, std::string text);
	void draw_to(sf::RenderWindow& window);
	bool is_pressed(sf::RenderWindow& window);
};


#endif // !Button_H

