#pragma once
#include <chrono>
#include "../Entity.h"
#include "../../Items/Bomb.h"
#include "../../Consts.h"
class Player : public Entity
{
public:
	//Player(int pos_x, int pos_y, unsigned int size_x, unsigned int size_y, int speed, int hp = 100, unsigned int quantity_bombs = 1);

	Player(sf::Vector2f position, sf::Texture& texture, sf::Vector2f size, unsigned int quantity_bombs, int speed = 5, int hp = PLAYER_LIVES);

	int get_hp();
	int get_quanity_bombs();

	void set_last_texture_number(int new_last_texture_number);

	int get_last_texture_number();

	void set_hp(int new_hp);
	void set_quanity_bombs(int new_quanity_bombs);

	bool on_bomb(std::vector<std::shared_ptr<Bomb>> bombs);

	// return true if current time is bigger than time_milliseconds
	bool can_textured_be_placed(int time_milliseconds);


	//reset time_since_texture_changed
	void place_texture();
private:
	int hp;
	int last_texture_number;

	std::chrono::steady_clock::time_point time_since_texture_changed = std::chrono::steady_clock::now();

	unsigned int quantity_bombs;
};