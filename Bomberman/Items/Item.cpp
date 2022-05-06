#include "Item.h"
#include "../Consts.h"


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

void Item::laad_immage_from_file(std::string image_path)
{
    item_sprite_.setOrigin(sprite_size_[0] / 2, sprite_size_[1] / 2);
    sf::Texture item_texture;

    if (!item_texture.loadFromFile(image_path))
    {
        throw std::exception("Image file not found");
    }
    item_sprite_.setTexture(item_texture);
}

void Item::draw_to(sf::RenderWindow& window) const
{
    window.draw(item_sprite_);
}

void Item::set_position(std::vector<int> position)
{
    item_sprite_.setPosition({position[0], position[1]});
}

sf::Vector2f Item::position() const
{
    return item_sprite_.getPosition();
}

void Item::rescale(sf::Vector2f scale)
{
    item_sprite_.scale(scale);
}

//void Item::set_position(std::vector<int> new_position)
//{
//	check_position_(new_position);
//	position_ = new_position;
//}
//
//std::vector<int> Item::position()
//{
//	return position_;
//}
//
//
//void Item::check_position_(std::vector<int> position)
//{
//	if (position.size() != DIMENSIONS) throw(std::exception("Incorect Dimensions"));
//	for (int i = 0; i < DIMENSIONS; i++)
//	{
//		if (position[i] > MAX_SIZE[i] || position[i] < 0) throw(std::exception("Incorect Position"));
//	}
//}

