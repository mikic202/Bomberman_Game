#include "Entity.h"


Entity::Entity()
{
	//pos_x = pos_y = speed = size_x = size_y = 0;
}

//Entity::Entity(int pos_x, int pos_y, unsigned int size_x, unsigned int size_y, int speed):
//		pos_x(pos_x), pos_y(pos_y), size_x(size_x), size_y(size_y), speed(speed){}

Entity::Entity(sf::Vector2f position, sf::Texture& texture, int speed) : texture(texture), speed(speed)
{
	this->sprite = sf::Sprite(texture);
	this->sprite.setPosition(position);
}

Entity::Entity(sf::Vector2f position, sf::Texture& texture, sf::Vector2f size, int speed) : Entity(position, texture, speed)
{
	this->sprite.scale(size);
}



void Entity::move(Direction direction){
		switch (direction)
		{
		case Direction::UP:
			this->sprite.move(0, -speed);
			break;
		case Direction::DOWN:
			this->sprite.move(0, speed);
			break;
		case Direction::LEFT:
			this->sprite.move(-speed, 0);
			break;
		case Direction::RIGHT:
			this->sprite.move(speed, 0);
			break;
		}
	}

void Entity::move(sf::Vector2f distance)
{
	this->sprite.move(distance);
}

void Entity::draw_to(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}

//int Entity::get_position_x(){
//	return pos_x;
//}
//
//int Entity::get_position_y(){
//	return pos_y;
//}

sf::Vector2f Entity::get_position()
{
	return this->sprite.getPosition();
}

//void Entity::set_position_x(int new_pos_x){
//	this->pos_x = new_pos_x;
//}
//
//void Entity::set_position_y(int new_pos_y){
//	this->pos_y = new_pos_y;
//}

void Entity::set_position(sf::Vector2f position)
{
	this->sprite.setPosition(position);
}

int Entity::get_speed(){
	return speed;
}

sf::Vector2f Entity::get_size()
{
	// get size of sprite
	return sf::Vector2f(
		this->sprite.getGlobalBounds().width,
		this->sprite.getGlobalBounds().height);
}

void Entity::set_speed(int new_speed){
	this->speed = new_speed;
}

sf::FloatRect Entity::get_global_bounds()
{
	return this->sprite.getGlobalBounds();
}

Entity::~Entity() 
{
};