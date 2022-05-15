#include "StoryModeBoard.h"
#include "../Exceptions/Item_exceptions.h"
#include "../Items/Box.h"


int StoryModeBoard::level_number()
{
    return level_number_;
}

StoryModeBoard::StoryModeBoard(int levels_pased, int number_of_players)
{
    level_number_ = levels_pased;
    /*for (int i = 1; i <= number_of_players; i++)
    {
        players_.push_back(Player());
    }*/
    generate_board_();
}

sf::Vector2f StoryModeBoard::door_position() const
{
    return door_sprite_.getPosition();
}

sf::FloatRect StoryModeBoard::get_door_global_bounds()
{
    return door_sprite_.getGlobalBounds();
}

void StoryModeBoard::generate_board_()
{
    int box_num = box_num_(level_number_);
    int max_box_strength = max_box_strength_(level_number_);

    place_walls_(size_[0], size_[1]);
    place_boxes_(size_[0], size_[1]);
    place_door_();
}

int StoryModeBoard::box_num_(int level_num) const
{
    int previous = 0;
    for (std::pair<int, int> dif : dificulty_map_)
    {
        if (dif.first > level_num)
        {
            break;
        }
        previous = dif.first;
    }
    return dificulty_map_.at(previous);
}

int StoryModeBoard::max_box_strength_(int level_num) const
{
    int previous = 0;
    for (std::pair<int, int> dif : box_strength_map_)
    {
        if (dif.first > level_num)
        {
            break;
        }
        previous = dif.first;
    }
    return box_strength_map_.at(previous);
}


void StoryModeBoard::place_boxes_(int size_x, int size_y)
{
    if (!box_texture_.loadFromFile(BOX_PATH))
    {
        throw (FliePathException());
    }
    if (size_y == -1) size_y = size_x;
    int box_num = box_num_(level_number_);
    int random_nuber_if_box;
    for (int y = 1; y <= size_y; y++)
    {
        for (int x = 1; x <= size_x; x++)
        {
            random_nuber_if_box = std::rand() % 2 + 1;
            if (((x % 2 == 1 && y % 2 == 0) || (y % 2 == 1)) && random_nuber_if_box == 1 && box_num > 0)
            {
                Box box({ float((x - 1) * GRID_SLOT_SIZE), float((y - 1) * GRID_SLOT_SIZE) }, max_box_strength_(level_number_), {.14286, .14286}, box_texture_);
                add_item(box);
                box_num--;
            }
        }
    }
}

void StoryModeBoard::place_door_()
{
    int door_pos_x = std::rand() % (size_[0] - size_[0] / 100 * where_door_can_ocure + 1) + size_[0] / 100 * where_door_can_ocure - 1;
    int door_pos_y = std::rand() % size_[1];
    if (door_pos_x % 2 == 0 && door_pos_y % 2 == 0)
    {
        door_pos_x++;
    }
    door_sprite_.setPosition({ door_pos_x, door_pos_y });
}
