#include "Enemy.h"

//Enemy::Enemy(int pos_x, int pos_y, unsigned int size_x, unsigned int size_y, int speed, int damage_to_player) : Entity(pos_x, pos_y, size_x, size_y, speed){
//	this->damage_to_player = damage_to_player;
//}

Enemy::Enemy()
{
}

Enemy::Enemy(sf::Vector2f position, sf::Texture &enemy_texture)
{
	this->sprite.setTexture(enemy_texture);
	this->sprite.setPosition(position);
}

int Enemy::get_damage_to_player()
{
	return damage_to_player;
}

void Enemy::set_damage_to_player(int new_damage)
{
	this->damage_to_player = damage_to_player;
}
