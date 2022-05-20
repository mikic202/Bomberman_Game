#ifndef StoryModeBoard_H
#define StoryModeBoard_H
#include "GameBoard.h"
#include "../Items/Door.h"
#include <map>


class StoryModeBoard : public GameBoard
{
private:
	int level_number_;
	Door door_;
	sf::Texture door_texture_;
	const int where_door_can_ocure = 50;
	std::map<int, int> dificulty_map_ {{0, 60}, {5, 100}, {10, 140}};// first - levels pased, second - boxes on board
	std::map<int, int> box_strength_map_{ {0, 1}, {5, 2}, {10, 3} };
	void generate_board_();
	int box_num_(int level_num) const;
	int max_box_strength_(int level_num) const;
	const std::vector<int> size_{ 30, 10 };
	void place_boxes_(int size_x, int size_y = -1);
	void place_door_();
public:
	void draw_to(sf::RenderWindow& window);
	int level_number();
	StoryModeBoard(int level_number, int number_of_players);
	sf::Vector2f door_position() const;
	sf::FloatRect get_door_global_bounds();
};


#endif // !StoryModeBoard_H
