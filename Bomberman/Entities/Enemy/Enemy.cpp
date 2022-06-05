#include "Enemy.h"

//Enemy::Enemy(int pos_x, int pos_y, unsigned int size_x, unsigned int size_y, int speed, int damage_to_player) : Entity(pos_x, pos_y, size_x, size_y, speed){
//	this->damage_to_player = damage_to_player;
//}

Enemy::Enemy()
{
	this->type = EnemyTypeMovement::RANDOM;
}

Enemy::Enemy(sf::Vector2f position, sf::Vector2f scale, sf::Texture &enemy_texture)
{
	this->sprite.setTexture(enemy_texture);
	this->sprite.setPosition(position);
	this->sprite.setScale(scale);
}

int Enemy::get_damage_to_player()
{
	return damage_to_player;
}

Enemy::Enemy(const Enemy& other)
{
	this->damage_to_player = other.damage_to_player;
	this->size_x = other.size_x;
	this->size_y = other.size_y;
	this->speed = other.speed;
	this->sprite = other.sprite;
	this->texture = other.texture;
	this->type = other.type;
	std::cout << "COPY CONSTRUCTOR OF ENEMY\n";
}

void Enemy::set_damage_to_player(int new_damage)
{
	this->damage_to_player = damage_to_player;
}

std::vector<std::pair<std::string, sf::Vector2i>> Enemy::get_available_directions(std::vector<std::shared_ptr<Wall>> walls)
{
	//sf::Vector2f coordinates_pos = this->get_position();
	
	// Check for next inter
	std::vector<std::pair<std::string, sf::Vector2i>> directions{
		std::make_pair("left", sf::Vector2i(-1, 0)),
		std::make_pair("right", sf::Vector2i(1, 0)),
		std::make_pair("top", sf::Vector2i(0, -1)),
		std::make_pair("bottom", sf::Vector2i(0, 1))
	};
	auto left = directions[0];
	auto right = directions[1];
	auto top = directions[2];
	auto bottom = directions[3];


	for (auto& wall_element : walls)
	{
		// Left element intersects check
		if (abs(wall_element.get()->get_global_bounds().left + wall_element.get()->get_global_bounds().width - this->get_position().x) <= 1)
			directions.erase(std::remove(directions.begin(), directions.end(), left), directions.end());
		// Right element intersects check
		if (wall_element.get()->position().x == this->get_position().x + 1)
			directions.erase(std::remove(directions.begin(), directions.end(), right), directions.end());
		// Top element intersects check
		if (wall_element.get()->position().y == this->get_position().y - 1)
			directions.erase(std::remove(directions.begin(), directions.end(), top), directions.end());
		// Bottom element intersects check
		if (wall_element.get()->position().y == this->get_position().y + 1)
			directions.erase(std::remove(directions.begin(), directions.end(), bottom), directions.end());
	}
	return directions;
}

void Enemy::move(std::vector<std::shared_ptr<Wall>> walls, std::vector<std::shared_ptr<Bomb>> bombs)
{

	// Movement is dependent on the type
	switch (this->type)
	{
	case EnemyTypeMovement::RANDOM:
		//this->sprite.getGlobalBounds().
		break;
	default:
		break;
	}
}
