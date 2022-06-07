//Miko³aj Chomanski

#include "Explosion.h"


Explosion::Explosion(sf::Vector2f position, sf::Vector2f scale)
{
	set_position(position);
	rescale(scale);
	explosion_time_ = std::chrono::high_resolution_clock::now();
}

Explosion::Explosion(sf::Vector2f position, sf::Vector2f scale, sf::Texture& explosion_texture)
{
	set_position(position);
	rescale(scale);
	item_sprite_.setTexture(explosion_texture);
	explosion_time_ = std::chrono::high_resolution_clock::now();
}

bool Explosion::did_end()
{
	return(duration_*1000 <= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - explosion_time_).count());
}
