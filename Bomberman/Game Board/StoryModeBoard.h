#ifndef StoryModeBoard_H
#define StoryModeBoard_H
#include "GameBoard.h"
#include <map>


class StoryModeBoard : public GameBoard
{
private:
	int level_number_;
	sf::Sprite door_sprite_;
	const int where_door_can_ocure = 50;
	std::map<int, int> dificulty_map_ {{0, 20}, {5, 30}, {10, 40}};// first - levels pased, second - boxes on board
	std::map<int, int> box_strength_map_{ {0, 1}, {5, 2}, {10, 3} };
	void generate_board_();
	int box_num_(int level_num) const;
	int max_box_strength_(int level_num) const;
	const std::vector<int> size_{ 50, 100 };
public:
	StoryModeBoard(int level_number, int number_of_players);
	sf::Vector2f door_position() const;
	sf::FloatRect get_door_global_bounds();
};


#endif // !StoryModeBoard_H
