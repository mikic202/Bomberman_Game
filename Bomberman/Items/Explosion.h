#ifndef Explosion_H
#define Explosion_H
#include "Wall.h"
#include"../Entities/Player/Player.h"
#include <chrono>


class Explosion : public Wall
{
private:
	const int duration_ = 1;
	std::chrono::time_point<std::chrono::steady_clock> explosion_time_;
public:
	Explosion() {};
	Explosion(sf::Vector2f position, sf::Vector2f scale);
	Explosion(sf::Vector2f position, sf::Vector2f scale, sf::Texture& explosion_texture);
	bool did_end();
};


#endif // !1
