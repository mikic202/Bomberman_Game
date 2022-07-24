#include "Entity.h"
#include <iostream>

Entity::Entity() { }


Entity::Entity(sf::Vector2f position, sf::Texture& texture, int speed) : texture(texture), speed(speed)
{
	this->sprite = sf::Sprite(texture);
	this->sprite.setPosition(position);
}

Entity::Entity(sf::Vector2f position, sf::Texture& texture, sf::Vector2f size, int speed) : Entity(position, texture, speed)
{
	this->sprite.scale(size);
}

void Entity::move(Direction direction)
{
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

sf::Vector2f Entity::get_position()
{
	return this->sprite.getPosition();
}

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

void Entity::scale(sf::Vector2f size)
{
	this->sprite.scale(size);
}

Entity::~Entity() { }
sf::FloatRect Entity::get_local_bounds()
{
	return sprite.getLocalBounds();
}
;