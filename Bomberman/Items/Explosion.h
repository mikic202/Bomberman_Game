#ifndef Explosion_H
#define Explosion_H
#include "Wall.h"
#include"../Entities/Player/Player.h"


class Explosion : public Wall
{
public:
	Explosion() {};
	Explosion(sf::Vector2f position, sf::Vector2f scale);
	Explosion(sf::Vector2f position, sf::Vector2f scale, sf::Texture& explosion_texture);
};


#endif // !1
