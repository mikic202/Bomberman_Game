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

bool Explosion::did_end()
{
	return(duration_ < std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - placement_time_).count());
}
