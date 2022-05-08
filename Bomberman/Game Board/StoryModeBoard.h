#ifndef StoryModeBoard_H
#define StoryModeBoard_H
#include "GameBoard.h"


class StoryModeBoard : public GameBoard
{
private:
	int max_num_boxes_;
	sf::Sprite door_sprite_;
	const int where_door_can_ocure = 50;
	void generate_board(int boxes_number);
public:
	StoryModeBoard(int levels_pased, int number_of_players);
	int dificulty() const;
	sf::Vector2f door_position() const;
	sf::FloatRect get_door_global_bounds();
};


#endif // !StoryModeBoard_H
