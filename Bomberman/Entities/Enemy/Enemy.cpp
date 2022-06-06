#include "Enemy.h"


Enemy::Enemy()
{
	srand(time(NULL));
	std::cout << "f\n\n";
	this->type = EnemyTypeMovement::RANDOM;
	this->movement_speed = 1;
}


Enemy::Enemy(sf::Vector2f position, sf::Vector2f scale, sf::Texture& enemy_texture, float movement_speed)
{
	srand(time(NULL));
	this->sprite.setTexture(enemy_texture);
	this->sprite.setPosition(position);
	this->sprite.setScale(scale);
	this->movement_direction = sf::Vector2i(-1, 0);
	this->movement_speed = movement_speed;
	this->type = EnemyTypeMovement::RANDOM;

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
	this->movement_speed = other.movement_speed;
}

void Enemy::set_damage_to_player(int new_damage)
{
	this->damage_to_player = damage_to_player;
}




std::vector<std::pair<std::string, sf::Vector2i>> Enemy::get_available_directions(std::vector<std::shared_ptr<Wall>> walls)
{
	std::vector<std::pair<std::string, sf::Vector2i>> directions{
		std::make_pair("left", sf::Vector2i(-1, 0)),
		std::make_pair("right", sf::Vector2i(1, 0)),
		std::make_pair("top", sf::Vector2i(0, -1)),
		std::make_pair("bottom", sf::Vector2i(0, 1))
	};
	std::pair<std::string, sf::Vector2i> left = directions[0];
	std::pair<std::string, sf::Vector2i> right = directions[1];
	std::pair<std::string, sf::Vector2i> top = directions[2];
	std::pair<std::string, sf::Vector2i> bottom = directions[3];


	//todo
	sf::Texture enemy_text;
	if (!enemy_text.loadFromFile(ENEMY_PATH)) std::cout << "wrong\n";


	Enemy enemy_right(sf::Vector2f(this->get_position().x + 1 * this->movement_speed, this->get_position().y), TEXTURE_SCALE, enemy_text);
	Enemy enemy_top(sf::Vector2f(this->get_position().x, this->get_position().y - 1 * this->movement_speed), TEXTURE_SCALE, enemy_text);
	Enemy enemy_bottom(sf::Vector2f(this->get_position().x, this->get_position().y + 1 * this->movement_speed), TEXTURE_SCALE, enemy_text);
	Enemy enemy_left(sf::Vector2f(this->get_position().x - 1 * this->movement_speed, this->get_position().y), TEXTURE_SCALE, enemy_text);



	// delete specific direction from directions if next position intersects border of screen or border of wall
	for (auto& wall : walls)
	{

		if (wall.get()->get_global_bounds().intersects(enemy_right.get_global_bounds())
			|| enemy_right.get_global_bounds().left + enemy_right.get_global_bounds().width >= WINDOW_WIDTH)
		{
			directions.erase(std::remove(directions.begin(), directions.end(), right), directions.end());
		}
		if (wall.get()->get_global_bounds().intersects(enemy_left.get_global_bounds())
			|| enemy_left.get_global_bounds().left <= 0)
		{

			directions.erase(std::remove(directions.begin(), directions.end(), left), directions.end());
		}

		if (wall.get()->get_global_bounds().intersects(enemy_top.get_global_bounds())
			|| enemy_top.get_global_bounds().top <= 0)
		{

			directions.erase(std::remove(directions.begin(), directions.end(), top), directions.end());
		}

		if (wall.get()->get_global_bounds().intersects(enemy_bottom.get_global_bounds())
			|| enemy_bottom.get_global_bounds().top + enemy_bottom.get_global_bounds().height >= WINDOW_HEIGHT)
		{


			directions.erase(std::remove(directions.begin(), directions.end(), bottom), directions.end());
		}
	}
	return directions;
}

void Enemy::move(std::vector<std::shared_ptr<Wall>> walls)
{

	// Movement is dependent on the type

	// More description about movement you can find here: https://gitlab-stud.elka.pw.edu.pl/dfokashc/proi-project/-/tree/main/Bomberman
	if (this->type == EnemyTypeMovement::RANDOM)
	{

		sf::Texture enemy_text;
		if (!enemy_text.loadFromFile(ENEMY_PATH)) std::cout << "bruh\n";

		Enemy next_pos_enemy(this->get_position(), TEXTURE_SCALE, enemy_text);
		next_pos_enemy.sprite.move(sf::Vector2f(movement_direction.x * movement_speed, movement_direction.y * movement_speed));


		// if next position of enemy intersects other object or border of screen than intersects_already is true
		bool intersects_already = false;
		// intersects border of screen check
		if (next_pos_enemy.get_global_bounds().left <= 0
			|| next_pos_enemy.get_global_bounds().left + next_pos_enemy.get_global_bounds().width >= WINDOW_WIDTH
			|| next_pos_enemy.get_global_bounds().top <= 0
			|| next_pos_enemy.get_global_bounds().top + next_pos_enemy.get_global_bounds().height >= WINDOW_HEIGHT)
		{
			intersects_already = true;
		}
		else
		{
			for (auto& wall : walls)
			{
				if (wall.get()->get_global_bounds().intersects(next_pos_enemy.get_global_bounds()))
				{
					intersects_already = true;
					break;
				}
			}
		}

		// if next position of enemy intersects object then change its direction
		if (intersects_already)
		{
			auto available_direction = get_available_directions(walls);
			int chosen_index = rand() % available_direction.size();
			this->movement_direction = available_direction[chosen_index].second;
		}
		this->sprite.move(sf::Vector2f(movement_direction.x * movement_speed, movement_direction.y * movement_speed));
	}
}