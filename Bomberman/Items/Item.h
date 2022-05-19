#ifndef Item_H
#define Item_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>


class Item
{
protected:
	std::string name_;
	//std::vector<int> position_;
	//void check_position_(std::vector<int> postion);
	sf::Sprite item_sprite_;
	std::vector<int> sprite_size_;
	sf::Texture item_texture_;
public:
	void move(sf::Vector2f move_distance);
	void set_name(std::string nem_name);
	std::string name() const;
	/*void set_position(std::vector<int> new_postion);
	std::vector<int> position();*/
	virtual sf::Sprite item_sprite() const;
	virtual void load_immage_from_file(std::string image_path);
	virtual void draw_to(sf::RenderWindow& window) const;
	void set_position(sf::Vector2f position);
	sf::Vector2f position() const;
	void rescale(sf::Vector2f scale);
};


#endif // !Item_H

