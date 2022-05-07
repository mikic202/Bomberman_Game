#pragma once
#include "../Entity.h"

class Player : public Entity
{
public:
	Player(int pos_x, int pos_y, unsigned int size_x, unsigned int size_y, int speed, int hp = 100, unsigned int quantity_bombs = 1);


	int get_hp();
	int get_quanity_bombs();

	void set_hp(int new_hp);
	void set_quanity_bombs(int new_quanity_bombs);

private:
	int hp;
	unsigned int quantity_bombs;
};