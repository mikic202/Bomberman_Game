#pragma once
#include "../../Items/Wall.h"
#include "../../Items/Bomb.h"
#include "../Entity.h"

// TODO CONSTRUCTORS FOR ENEMY
class Enemy : public Entity
{
public:
	//Enemy(int pos_x, int pos_y, unsigned int size_x, unsigned int size_y, int speed, int damage_to_player);
	Enemy();
	Enemy(sf::Vector2f position, sf::Vector2f scale, sf::Texture &enemy_texture );
	int get_damage_to_player();

	void set_damage_to_player(int new_damage);

	void move(std::vector<std::shared_ptr<Wall>> walls, std::vector<std::shared_ptr<Bomb>> bombs);
private:
	int damage_to_player = 0;
};