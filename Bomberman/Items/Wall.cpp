#include "Wall.h"


sf::FloatRect Wall::get_global_bounds()
{
	return item_sprite_.getGlobalBounds();
}

Wall::Wall(sf::Vector2f position, sf::Vector2f scale)
{
	set_position(position);
	rescale(scale);
	load_immage_from_file(wall_texture_path_);
}