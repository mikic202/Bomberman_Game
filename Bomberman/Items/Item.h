//Miko³aj Chomanski

#ifndef Item_H
#define Item_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>


class Item
{
protected:
	std::string name_;
	sf::Sprite item_sprite_;
	std::vector<int> sprite_size_;
public:
	void move(sf::Vector2f move_distance);
	void set_name(std::string nem_name);
	std::string name() const;
	virtual sf::Sprite item_sprite() const;
	virtual void draw_to(sf::RenderWindow& window) const;
	void set_position(sf::Vector2f position);
	sf::Vector2f position() const;
	void rescale(sf::Vector2f scale);
};


#endif // !Item_H

