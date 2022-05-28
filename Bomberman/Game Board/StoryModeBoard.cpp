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

StoryModeBoard::StoryModeBoard(int level_number, int number_of_players, sf::Texture &wall_texture, sf::Texture &box_texture, sf::Texture &door_texture)
{
    level_number_ = level_number;
    wall_texture_ = wall_texture;
    box_texture_ = box_texture;
    door_texture_ = door_texture;
    /*for (int i = 1; i <= number_of_players; i++)
    {
        players_.push_back(Player());
    }*/
    generate_board_(wall_texture, box_texture, door_texture);
}

sf::Vector2f StoryModeBoard::door_position() const
{
    return door_.position();
}

sf::FloatRect StoryModeBoard::get_door_global_bounds()
{
    return door_.get_global_bounds();
}

void StoryModeBoard::move_items(sf::Vector2f distance)
{
    for (auto a : items_on_board_)
    {
        a->move(distance);
    }
    door_.move(distance);
}

void StoryModeBoard::reset_board(int level_number, sf::Texture& wall_texture, sf::Texture& box_texture, sf::Texture& door_texture)
{
    level_number_ = level_number;
    items_on_board_.clear();
    generate_board_(wall_texture, box_texture, door_texture);

}

void StoryModeBoard::generate_board_(sf::Texture& wall_texture, sf::Texture& box_texture, sf::Texture& door_texture)
{
    place_walls_(size_[0], size_[1], wall_texture);
    place_boxes_(size_[0], size_[1], box_texture);
    place_door_(door_texture);
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


void StoryModeBoard::place_boxes_(int size_x, int size_y, sf::Texture& box_texture)
{
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
                Box box({ float((x - 1) * GRID_SLOT_SIZE), float((y - 1) * GRID_SLOT_SIZE) }, max_box_strength_(level_number_), TEXTURE_SCALE, box_texture);
                add_item(box);
                box_num--;
            }
        }
    }
}

void StoryModeBoard::place_door_(sf::Texture& door_texture)
{
    srand(time(NULL));
    int door_pos_x = std::rand() % (size_[0] - (size_[0] * where_door_can_ocure / 100)) + size_[0] * where_door_can_ocure / 100 - 1;
    int door_pos_y = std::rand() % size_[1];
    if (door_pos_x % 2 == 1 && door_pos_y % 2 == 1)
    {
        door_pos_x++;
    }
    door_ = Door({ float(door_pos_x)*GRID_SLOT_SIZE, float(door_pos_y)*GRID_SLOT_SIZE }, TEXTURE_SCALE, door_texture);
    items_on_board_.push_back(std::make_shared<Wall>(Door({ float(door_pos_x) * GRID_SLOT_SIZE, float(door_pos_y) * GRID_SLOT_SIZE }, TEXTURE_SCALE, door_texture)));
}
