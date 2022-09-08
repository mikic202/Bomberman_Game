//Miko³aj Chomanski

#include "VersusModeBoard.h"

VersusModeBoard::VersusModeBoard(int size, sf::Texture& wall_texture, sf::Texture& box_texture)
{
	size_ = size;
	generate_board_(wall_texture, box_texture);
}

int VersusModeBoard::size()
{
	return size_;
}

void VersusModeBoard::generate_board_(sf::Texture& wall_texture, sf::Texture& box_texture)
{
	place_boxes_(size_, size_, box_texture);
	place_walls_(size_, size_, wall_texture);
}
