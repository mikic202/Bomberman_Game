//Miko³aj Chomanski

#include "Door.h"


Door::Door(sf::Vector2f position, sf::Vector2f scale, sf::Texture& wall_texture)
{
	set_position({ position.x + 4.f, position.y + 4.f });
	rescale(scale);
	item_sprite_.setTexture(wall_texture);
	//load_immage_from_file(wall_texture_path_);
}


Door::Door(sf::Vector2f position, sf::Vector2f scale)
{
	set_position(position);
	rescale(scale);
	load_immage_from_file(door_texture_path_);
}
