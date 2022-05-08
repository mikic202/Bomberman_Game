#include "StoryModeBoard.h"


StoryModeBoard::StoryModeBoard(int levels_pased, int number_of_players)
{
    max_boxes_on_board_ = dificulty_(levels_pased);
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

int StoryModeBoard::dificulty_(int levels_pased) const
{
    int previous = 0;
    for (std::pair<int, int> dif : dificulty_map_)
    {
        if (dif.first > levels_pased)
        {
            break;
        }
        previous = dif.first;
    }
    return dificulty_map_.at(previous);
}
