#include "Item.h"
#include "../Consts.h"


void Item::set_name(std::string new_name)
{
	name_ = new_name;
}

std::string Item::name()
{
	return name_;
}

void Item::set_position(std::vector<int> new_position)
{
	check_position_(new_position);
	position_ = new_position;
}

std::vector<int> Item::position()
{
	return position_;
}


void Item::check_position_(std::vector<int> position)
{
	if (position.size() != DIMENSIONS) throw(std::exception("Incorect Dimensions"));
	for (int i = 0; i < DIMENSIONS; i++)
	{
		if (position[i] > MAX_SIZE[i] || position[i] < 0) throw(std::exception("Incorect Position"));
	}
}