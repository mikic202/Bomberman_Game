#ifndef GameBoard_H
#define GameBoard_H
#include <SFML/Graphics.hpp>
#include <vector>
#include"../Items/Wall.h"
#include"../Entities/Player/Player.h"
#include"../Consts.h"

class GameBoard
{
protected:
	sf::Texture background_;
	std::vector<std::shared_ptr<Wall> > items_on_board_;
	int max_boxes_on_board_;
	std::vector<std::shared_ptr<Player> > players_;
	void place_walls_(int size_x, int size_y, sf::Texture& wall_texture);
	sf::Texture wall_texture_;
	sf::Texture box_texture_;
	virtual void generate_board_(sf::Texture& wall_texture, sf::Texture& box_texture);
	virtual void place_boxes_(int size_x, int size_y, sf::Texture& box_texture);
public:
	void remove_item(int position);
	void load_bacground(std::string backgroung_image);
	sf::Texture bacground();
	template<typename T> void add_item(T new_item);
	std::vector<std::shared_ptr<Wall> > items();
	std::shared_ptr<Wall> item(int item_position);
	std::vector<std::shared_ptr<Player> > players();
	void add_player(Player new_player);
	virtual void draw_to(sf::RenderWindow& window);
	virtual void move_items(sf::Vector2f distance);
	virtual sf::FloatRect get_door_global_bounds() { return sf::FloatRect(); };
	virtual void reset_board(int level_number, sf::Texture& wall_texture, sf::Texture& box_texture, sf::Texture& door_texture);
	virtual int level_number() { return 0; };
};


template<typename T> 
inline void GameBoard::add_item(T new_item)
{
	items_on_board_.push_back(std::make_shared<T>(new_item));
}


#endif