#ifndef VersusModeBoard_H
#define VersusModeBoard_H
#include "GameBoard.h"

class VersusModeBoard : public GameBoard
{
private:
	int size_;
	void generate_board_(sf::Texture& wall_texture, sf::Texture& box_texture);
public:
	VersusModeBoard(int size, sf::Texture& wall_texture, sf::Texture& box_texture);
	int size();
};


#endif // !VersusModeBoard_H

