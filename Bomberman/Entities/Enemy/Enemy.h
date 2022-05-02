#pragma once
#include "../Entity.h"

class Enemy : public Entity
{
public:
	Enemy(int pos_x, int pos_y, unsigned int size_x, unsigned int size_y, int speed, int damage_to_player);

	int get_damage_to_player();

	void set_damage_to_player(int new_damage);
private:
	int damage_to_player = 0;
};