//Miko³aj Chomanski

#include "GameBoard.h"
#include "../Exceptions/Item_exceptions.h"
#include "../Items/Box.h"
#include <time.h>

void GameBoard::remove_item(int position)
{
	items_on_board_.erase(items_on_board_.begin() + position);
}

void GameBoard::load_bacground(std::string backgroung_image)
{
	if (!background_.loadFromFile(backgroung_image))
	{
		throw (FliePathException());
	}
}

sf::Texture GameBoard::bacground()
{
	return background_;
}

std::vector<std::shared_ptr<Wall>> GameBoard::items()
{
	return items_on_board_;
}

std::shared_ptr<Wall> GameBoard::item(int item_position)
{
	return items_on_board_[item_position];
}

void GameBoard::draw_to(sf::RenderWindow& window)
{
	for (std::shared_ptr<Item> item : items_on_board_)
	{
		item->draw_to(window);
	}
}

void GameBoard::move_items(sf::Vector2f distance)
{
	for (auto a : items_on_board_)
	{
		a->move(distance);
	}
}

void GameBoard::reset_board(int level_number, sf::Texture& wall_texture, sf::Texture& box_texture, sf::Texture& door_texture)
{
	items_on_board_.clear();
	generate_board_(wall_texture, box_texture);
}

void GameBoard::place_walls_(int size_x, int size_y, sf::Texture& wall_texture)
{
	srand(time(NULL));
	if (size_y == -1) size_y = size_x;
	for (int y = 1; y <= size_y; y++)
	{
		if (y % 2 == 0)
		{
			for (int x = 1; x <= size_x; x++)
			{
				if (x % 2 == 0)
				{
					Wall wall({ float((x-1) * GRID_SLOT_SIZE), float((y-1) * GRID_SLOT_SIZE) }, TEXTURE_SCALE, wall_texture);
					add_item(wall);
				}
			}
		}
	}
	for (int x = 1; x <= size_x; x++)
	{
		Wall wall({ float((x - 1) * GRID_SLOT_SIZE), -GRID_SLOT_SIZE }, TEXTURE_SCALE, wall_texture);
		add_item(wall);
		wall.set_position({ float((x - 1) * GRID_SLOT_SIZE), float(size_y* GRID_SLOT_SIZE) });
		add_item(wall);
	}
	for (int y = 1; y <= size_y; y++)
	{
		Wall wall({- GRID_SLOT_SIZE - 5, float((y - 1) * GRID_SLOT_SIZE)}, TEXTURE_SCALE, wall_texture);
		add_item(wall);
		wall.set_position({float(size_x*GRID_SLOT_SIZE), float((y - 1) * GRID_SLOT_SIZE)});
		add_item(wall);
	}
}

void GameBoard::generate_board_(sf::Texture& wall_texture, sf::Texture& box_texture)
{
	place_walls_(GAME_BOARD_SIZE, GAME_BOARD_SIZE, wall_texture);
	place_boxes_(GAME_BOARD_SIZE, GAME_BOARD_SIZE, box_texture);
}

void GameBoard::place_boxes_(int size_x, int size_y, sf::Texture& box_texture)
{
	srand(time(NULL));
	if (size_y == -1) size_y = size_x;
	int random_nuber_if_box;
	for (int y = 1; y <= size_y; y++)
	{
		for (int x = 1; x <= size_x; x++)
		{
			random_nuber_if_box = std::rand() % 3 + 1;
			if (((x % 2 == 1 && y % 2 == 0) || (y % 2 == 1)) && random_nuber_if_box != 1 && (x > 2 || y > 2)&&(x < size_x - 1 || y < size_y - 1))
			{
				Box box({ float((x - 1) * GRID_SLOT_SIZE), float((y - 1) * GRID_SLOT_SIZE) }, 1, TEXTURE_SCALE, box_texture);
				add_item(box);
			}
		}
	}
}
