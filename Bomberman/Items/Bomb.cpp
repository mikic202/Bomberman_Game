#include "Bomb.h"
#include "../Consts.h"
#include <cmath>
#include "../Exceptions/Item_exceptions.h"


Bomb::Bomb(sf::Vector2f position, int radius, int delay, int strength, sf::Vector2f scale)
{
	set_name("Bomb");
	set_position(position);
	set_radius(radius);
	set_delay(delay);
	set_strength(strength);
	rescale(scale);
	load_immage_from_file(texture_path_);
	placement_time_ = std::chrono::high_resolution_clock::now();
}

void Bomb::set_radius(int new_radius)
{
	radius_ = new_radius;
}

int Bomb::radius()
{
	return radius_;
}

void Bomb::set_delay(int new_delay)
{
	if (new_delay > MAX_EXPLOSION_DELAY) throw(DelayException());
	delay_ = new_delay;
}

int Bomb::delay()
{
	return delay_;
}

void Bomb::set_strength(int new_strength)
{
	strength_ = new_strength;
}

int Bomb::strength()
{
	return strength_;
}

bool Bomb::did_blow()
{
	return(delay_ < std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - placement_time_).count());
}
