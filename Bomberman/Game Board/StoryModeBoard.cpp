#include "StoryModeBoard.h"
#include "../Exceptions/Item_exceptions.h"
#include "../Items/Box.h"
#include <time.h>


void StoryModeBoard::draw_to(sf::RenderWindow& window)
{
    door_.draw_to(window);
    for (std::shared_ptr<Item> item : items_on_board_)
    {
        item->draw_to(window);
    }
}

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
    return door_.position();
}

sf::FloatRect StoryModeBoard::get_door_global_bounds()
{
    return door_.get_global_bounds();
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
    srand(time(NULL));
    if (size_y == -1) size_y = size_x;
    int box_num = box_num_(level_number_);
    int random_nuber_if_box;
    for (int y = 1; y <= size_y; y++)
    {
        for (int x = 1; x <= size_x; x++)
        {
            random_nuber_if_box = std::rand() % 3 + 1;
            if (((x % 2 == 1 && y % 2 == 0) || (y % 2 == 1)) && random_nuber_if_box == 1 && box_num > 0 && (x >2 || y > 2))
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
    srand(time(NULL));
    int door_pos_x = std::rand() % (size_[0] - (size_[0] * where_door_can_ocure / 100)) + size_[0] * where_door_can_ocure / 100 - 1;
    int door_pos_y = std::rand() % size_[1];
    if (door_pos_x % 2 == 1 && door_pos_y % 2 == 1)
    {
        door_pos_x++;
    }
    if (!door_texture_.loadFromFile(DOOR_PATH))
    {
        throw (FliePathException());
    }
    door_ = Door({ float(door_pos_x)*GRID_SLOT_SIZE, float(door_pos_y)*GRID_SLOT_SIZE }, { .14286, .14286 }, door_texture_);
}
