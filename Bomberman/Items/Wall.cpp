#include "Wall.h"


sf::FloatRect Wall::get_global_bounds()
{
	return item_sprite_.getGlobalBounds();
}