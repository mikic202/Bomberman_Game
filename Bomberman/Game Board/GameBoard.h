#ifndef GameBoard_H
#define GameBoard_H
#include <SFML/Graphics.hpp>
#include <vector>
#include"../Items/Item.h"

class GameBoard
{
protected:
	sf::Texture background;
	std::vector<std::shared_ptr<Item> > items_on_board;
	int max_boxes_on_board;
public:
	void load_bacground(std::string backgroung_image);
	sf::Texture bacground();
	template<typename T> void add_item(T new_item);
	std::vector<std::shared_ptr<Item> > items();
	std::shared_ptr<Item> item(int item_position);
};


template<typename T> 
inline void GameBoard::add_item(T new_item)
{
	items_on_board.push_back(new_item);
}


#endif