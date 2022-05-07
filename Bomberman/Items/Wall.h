#ifndef Wall_H
#define Wall_H
#include "Item.h"


class Wall : public Item
{
public:
	Wall() {};
	Wall(std::vector<int> position, sf::Vector2f scale, std::string image_path);
	sf::FloatRect get_global_bounds();
};


#endif // !Wall_H

