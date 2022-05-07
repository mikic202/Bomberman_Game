#include "Wall.h"


sf::FloatRect Wall::get_global_bounds()
{
	return item_sprite_.getGlobalBounds();
}

Wall::Wall(std::vector<int> position, sf::Vector2f scale, std::string image_path)
{
	set_position(position);
	rescale(scale);
	load_immage_from_file(image_path);
}