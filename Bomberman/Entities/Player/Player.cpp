#include "Player.h"

Player::Player(int pos_x, int pos_y, unsigned int size_x, unsigned int size_y, int speed, int hp, unsigned int quantity_bombs) : Entity(pos_x, pos_y, size_x, size_y, speed) {
	this->hp = hp;
	this->quantity_bombs = quantity_bombs;
}

int Player::get_hp(){
	return hp;
}

int Player::get_quanity_bombs(){
	return quantity_bombs;
}

void Player::set_hp(int new_hp){
	this->hp = new_hp;
}

void Player::set_quanity_bombs(int new_quanity_bombs){
	this->quantity_bombs = new_quanity_bombs;
}

