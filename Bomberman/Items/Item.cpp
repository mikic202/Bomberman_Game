//Miko³aj Chomanski

#include "Item.h"
#include "../Consts.h"
#include "../Exceptions/Item_exceptions.h"


void Item::move(sf::Vector2f move_distance)
{
    item_sprite_.move(move_distance);
}

void Item::set_name(std::string new_name)
{
	name_ = new_name;
}

std::string Item::name() const
{
	return name_;
}

sf::Sprite Item::item_sprite() const
{
	return item_sprite_;
}

void Item::draw_to(sf::RenderWindow& window) const
{
    window.draw(item_sprite_);
}

void Item::set_position(sf::Vector2f position)
{
    item_sprite_.setPosition(position);
}

sf::Vector2f Item::position() const
{
    return item_sprite_.getPosition();
}

void Item::rescale(sf::Vector2f scale)
{
    item_sprite_.scale(scale);
}
