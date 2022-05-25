#include "GameBoard.h"
#include "../Exceptions/Item_exceptions.h"
#include "../Items/Box.h"
#include <time.h>

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

std::vector<std::shared_ptr<Player>> GameBoard::players()
{
	return players_;
}

void GameBoard::add_player(Player new_player)
{
	std::shared_ptr<Player> ptr = std::make_shared<Player>(new_player);
	players_.push_back(std::move(ptr));;
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

void GameBoard::place_walls_(int size_x, int size_y)
{
	if (!wall_texture_.loadFromFile(WALL_PATH))
	{
		throw (FliePathException());
	}
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
					Wall wall({ float((x-1) * GRID_SLOT_SIZE), float((y-1) * GRID_SLOT_SIZE) }, TEXTURE_SCALE, wall_texture_);
					add_item(wall);
				}
			}
		}
	}
}

void GameBoard::generate_board_()
{
	place_walls_(MAX_SIZE[0], MAX_SIZE[1]);
	place_boxes_(MAX_SIZE[0], MAX_SIZE[1]);
}

void GameBoard::place_boxes_(int size_x, int size_y)
{
	if (!box_texture_.loadFromFile(BOX_PATH))
	{
		throw (FliePathException());
	}
	if (size_y == -1) size_y = size_x;
	int random_nuber_if_box;
	for (int y = 1; y <= size_y; y++)
	{
		for (int x = 1; x <= size_x; x++)
		{
			random_nuber_if_box = std::rand() % 3 + 1;
			if (((x % 2 == 1 && y % 2 == 0) || (y % 2 == 1)) && random_nuber_if_box != 1)
			{
				Box box({ float((x - 1) * GRID_SLOT_SIZE), float((y - 1) * GRID_SLOT_SIZE) }, 1, TEXTURE_SCALE, box_texture_);
				add_item(box);
			}
		}
	}
}
