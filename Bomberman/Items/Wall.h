#ifndef Wall_H
#define Wall_H
#include "Item.h"


class Wall : public Item
{
private:
	std::string wall_texture_path_ = "";
public:
	Wall() {};
	Wall(sf::Vector2f position, sf::Vector2f scale);
	sf::FloatRect get_global_bounds();
};


#endif // !Wall_H

