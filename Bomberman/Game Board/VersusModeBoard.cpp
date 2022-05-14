#include "VersusModeBoard.h"

VersusModeBoard::VersusModeBoard(int size)
{
	size_ = size;
}

int VersusModeBoard::size()
{
	return size_;
}

void VersusModeBoard::generate_board_()
{
	place_boxes_(size_);
	place_walls_(size_);
}
