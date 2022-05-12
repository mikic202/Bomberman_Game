#include "Box.h"


Box::Box(sf::Vector2f position, int hits_to_brake, sf::Vector2f scale)
{
	set_position(position);
	rescale(scale);
	load_immage_from_file(box_texture_path_);
	set_hits_to_brake(hits_to_brake);
}

void Box::set_hits_to_brake(int new_hits)
{
	if (new_hits <= 0) throw(std::invalid_argument("Can't set box to be broken"));
	hits_to_brake_ = new_hits;
}

int Box::hits_to_brake()
{
	return hits_to_brake_;
}

bool Box::hit(int strength)
{
	hits_to_brake_ -= strength;
	return chek_if_broken_();
}

bool Box::chek_if_broken_()
{
	if (hits_to_brake_ > 0)
		return true;
	return false;
}