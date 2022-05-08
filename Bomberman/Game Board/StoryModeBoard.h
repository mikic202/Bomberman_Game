#ifndef StoryModeBoard_H
#define StoryModeBoard_H
#include "GameBoard.h"
#include <map>


class StoryModeBoard : public GameBoard
{
private:
	int max_num_boxes_;
	sf::Sprite door_sprite_;
	const int where_door_can_ocure = 50;
	const std::map<int, int> dificulty_map_ {{0, 20}, {5, 30}, {10, 40}};// first - levels pased, second - boxes on board
	void generate_board_(int boxes_number);
	int dificulty_(int levels_pased) const;
public:
	StoryModeBoard(int levels_pased, int number_of_players);
	sf::Vector2f door_position() const;
	sf::FloatRect get_door_global_bounds();
};


#endif // !StoryModeBoard_H
