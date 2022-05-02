#include "Entity.h"


Entity::Entity(int pos_x, int pos_y, unsigned int size_x, unsigned int size_y, int speed):
		pos_x(pos_x), pos_y(pos_y), size_x(size_x), size_y(size_y), speed(speed){}

void Entity::move(Direction direction){
		switch (direction)
		{
		case Direction::UP:
			pos_y -= speed;
			break;
		case Direction::DOWN:
			pos_y += speed;
			break;
		case Direction::LEFT:
			pos_x -= speed;
			break;
		case Direction::RIGHT:
			pos_x += speed;
			break;
		}
	}

int Entity::get_position_x(){
	return pos_x;
}

int Entity::get_position_y(){
	return pos_y;
}

void Entity::set_position_x(int new_pos_x){
	this->pos_x = new_pos_x;
}

void Entity::set_position_y(int new_pos_y){
	this->pos_y = new_pos_y;
}

int Entity::get_speed(){
	return speed;
}

void Entity::set_speed(int new_speed){
	this->speed = new_speed;
}

Entity::~Entity() {};