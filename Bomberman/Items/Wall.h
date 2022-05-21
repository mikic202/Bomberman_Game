#ifndef Wall_H
#define Wall_H
#include "Item.h"
#include "../Consts.h"
#include "../Entities/Player/Player.h"


class Wall : public Item
{
private:
	std::string wall_texture_path_ = BOMB_PATH;
public:
	Wall() {};
	Wall(sf::Vector2f position, sf::Vector2f scale);
	Wall(sf::Vector2f position, sf::Vector2f scale, sf::Texture& wall_texture);
	sf::FloatRect get_global_bounds();
	bool is_coloding_player(Player& player);
};


#endif // !Wall_H

