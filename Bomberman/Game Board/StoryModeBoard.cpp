#include "StoryModeBoard.h"


StoryModeBoard::StoryModeBoard(int levels_pased, int number_of_players)
{
    level_number_ = levels_pased;
    /*for (int i = 1; i <= number_of_players; i++)
    {
        players_.push_back(Player());
    }*/
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

