//Miko³aj Chomanski

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
	const int where_door_can_ocure = 50;
	std::map<int, int> dificulty_map_ {{0, 40}, {8, 50}, {16, 60}};// first - levels pased, second - boxes on board
	std::map<int, int> box_strength_map_{ {0, 1}, {10, 2} };
	void generate_board_(sf::Texture& wall_texture, sf::Texture& box_texture, sf::Texture& door_texture);
	int box_num_(int level_num) const;
	int max_box_strength_(int level_num) const;
	const std::vector<int> size_ = STORY_SIZE;
	void place_boxes_(int size_x, int size_y, sf::Texture& box_texture);
	void place_door_(sf::Texture& door_texture);
public:
	void draw_to(sf::RenderWindow& window);
	int level_number();
	StoryModeBoard(int level_number, int number_of_players, sf::Texture &wall_texture, sf::Texture &box_texture, sf::Texture &door_texture);
	sf::Vector2f door_position() const;
	sf::FloatRect get_door_global_bounds();
	void move_items(sf::Vector2f distance);
	virtual void reset_board(int level_number, sf::Texture& wall_texture, sf::Texture& box_texture, sf::Texture& door_texture);
};


#endif // !StoryModeBoard_H
