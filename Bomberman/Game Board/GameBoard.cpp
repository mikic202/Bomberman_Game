#include "GameBoard.h"
#include "../Exceptions/Item_exceptions.h"

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

std::vector<std::shared_ptr<Item>> GameBoard::items()
{
	return items_on_board_;
}

std::shared_ptr<Item> GameBoard::item(int item_position)
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
