#pragma once
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



	void set_hp(int new_hp);
	void set_quanity_bombs(int new_quanity_bombs);

	bool on_bomb(std::vector<std::shared_ptr<Bomb>> bombs);

private:
	int hp;
	unsigned int quantity_bombs;
};