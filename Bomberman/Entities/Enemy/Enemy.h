#pragma once
#include "../../Items/Wall.h"
#include "../../Items/Bomb.h"
#include "../Entity.h"
#include "../../Exceptions/enemy_exteptions.h"
#include <time.h>

enum EnemyTypeMovement
{
	RANDOM
};

class Enemy : public Entity
{
public:
	Enemy();
	Enemy(sf::Vector2f position, sf::Vector2f scale, sf::Texture& texture, float movement_speed = 2);
	int get_damage_to_player();


	Enemy(const Enemy& other);
	void set_damage_to_player(int new_damage);

	std::vector<std::pair<std::string, sf::Vector2i>> get_available_directions(std::vector<std::shared_ptr<Wall>> walls);

	void move(std::vector<std::shared_ptr<Wall>> walls);
protected:
	float movement_speed;
	EnemyTypeMovement type;
	sf::Vector2i movement_direction;

	int damage_to_player = 0;
};