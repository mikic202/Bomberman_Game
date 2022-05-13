#ifndef Wall_H
#define Wall_H
#include "Item.h"
#include "../Consts.h"


class Wall : public Item
{
private:
	std::string wall_texture_path_ = BOMB_PATH;
public:
	Wall() {};
	Wall(sf::Vector2f position, sf::Vector2f scale);
	Wall(sf::Vector2f position, sf::Vector2f scale, sf::Texture& wall_texture);
	sf::FloatRect get_global_bounds();
};


#endif // !Wall_H

