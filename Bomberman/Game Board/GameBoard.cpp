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
