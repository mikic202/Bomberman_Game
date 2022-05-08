#ifndef GameBoard_H
#define GameBoard_H
#include <SFML/Graphics.hpp>
#include <vector>
#include"../Items/Item.h"
#include"../Entities/Player/Player.h"

class GameBoard
{
protected:
	sf::Texture background_;
	std::vector<std::shared_ptr<Item> > items_on_board_;
	int max_boxes_on_board_;
	std::vector<std::shared_ptr<Player> > players_;
public:
	void load_bacground(std::string backgroung_image);
	sf::Texture bacground();
	template<typename T> void add_item(T new_item);
	std::vector<std::shared_ptr<Item> > items();
	std::shared_ptr<Item> item(int item_position);
	std::vector<std::shared_ptr<Player> > players();
	void add_player(Player new_player);
};


template<typename T> 
inline void GameBoard::add_item(T new_item)
{
	std::shared_ptr<Item> ptr = std::make_shared<T>(new_item);
	items_on_board_.push_back(std::move(ptr));
}


#endif