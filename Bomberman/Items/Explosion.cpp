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