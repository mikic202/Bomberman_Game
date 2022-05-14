#ifndef Explosion_H
#define Explosion_H
#include "Wall.h"


class Explosion : public Wall
{
	Explosion() {};
	Explosion(sf::Vector2f position, sf::Vector2f scale);
	Explosion(sf::Vector2f position, sf::Vector2f scale, sf::Texture explosion_texture);
};


#endif // !1
