#ifndef Explosion_H
#define Explosion_H
#include "Item.h"


class Explosion : public Item
{
	Explosion() {};
	Explosion(sf::Vector2f position, sf::Vector2f scale);
	Explosion(sf::Vector2f position, sf::Vector2f scale, sf::Texture explosion_texture);
};


#endif // !1
