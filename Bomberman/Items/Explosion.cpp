#include "Explosion.h"


Explosion::Explosion(sf::Vector2f position, sf::Vector2f scale)
{
	set_position(position);
	rescale(scale);
}

Explosion::Explosion(sf::Vector2f position, sf::Vector2f scale, sf::Texture& explosion_texture)
{
	set_position(position);
	rescale(scale);
	item_sprite_.setTexture(explosion_texture);
}

bool Explosion::is_col_player(Player& player)
{
	//return get_global_bounds().intersects(player.get_global_bounds());
	return true;
}