//Miko³aj Chomanski

#include "Wall.h"


sf::FloatRect Wall::get_global_bounds()
{
	return item_sprite_.getGlobalBounds();
}

bool Wall::is_coloding_player(std::shared_ptr< Player> player)
{
	return get_global_bounds().intersects(player->get_global_bounds());
}

Wall::Wall(sf::Vector2f position, sf::Vector2f scale, sf::Texture& wall_texture)
{
	set_position(position);
	rescale(scale);
	item_sprite_.setTexture(wall_texture);
	//load_immage_from_file(wall_texture_path_);
}

Wall::Wall(sf::Vector2f position, sf::Vector2f scale)
{
	set_position(position);
	rescale(scale);
	load_immage_from_file(wall_texture_path_);
}