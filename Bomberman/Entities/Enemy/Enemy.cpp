#include "Enemy.h"


Enemy::Enemy()
{
	this->type = EnemyTypeMovement::RANDOM;
	this->movement_speed = 1;
}


Enemy::Enemy(sf::Vector2f position, sf::Vector2f scale, sf::Texture& enemy_texture, float movement_speed)
{
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

std::vector<std::pair<std::string, sf::Vector2i>> Enemy::get_available_directions(std::vector<std::shared_ptr<Wall>> walls, std::vector<std::shared_ptr<Bomb>> bombs, std::vector<std::shared_ptr<Player> > players)
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


	sf::Texture enemy_text;
	if (!enemy_text.loadFromFile(ENEMY_PATH)) 
		throw TextureCanNotBeLoadedException("Can not load texture for enemy from ENEMY_PATH variable!");

	Enemy enemy_right(sf::Vector2f(this->get_position().x + 5 * this->movement_speed, this->get_position().y), TEXTURE_SCALE, enemy_text);
	Enemy enemy_top(sf::Vector2f(this->get_position().x, this->get_position().y - 5 * this->movement_speed), TEXTURE_SCALE, enemy_text);
	Enemy enemy_bottom(sf::Vector2f(this->get_position().x, this->get_position().y + 5 * this->movement_speed), TEXTURE_SCALE, enemy_text);
	Enemy enemy_left(sf::Vector2f(this->get_position().x - 5 * this->movement_speed, this->get_position().y), TEXTURE_SCALE, enemy_text);



	// delete specific direction from directions if next position intersects border of screen or border of wall
	for (int i = 0; i < walls.size(); i++)
	{
		auto wall = walls[i];

		if (wall.get()->get_global_bounds().intersects(enemy_right.get_global_bounds()))
		{
			directions.erase(std::remove(directions.begin(), directions.end(), right), directions.end());
		}
		if (wall.get()->get_global_bounds().intersects(enemy_left.get_global_bounds()))
		{

			directions.erase(std::remove(directions.begin(), directions.end(), left), directions.end());
		}

		if (wall.get()->get_global_bounds().intersects(enemy_top.get_global_bounds()))
		{

			directions.erase(std::remove(directions.begin(), directions.end(), top), directions.end());
		}

		if (wall.get()->get_global_bounds().intersects(enemy_bottom.get_global_bounds()))
		{
			directions.erase(std::remove(directions.begin(), directions.end(), bottom), directions.end());
		}
	}

	for (auto bomb : bombs)
	{
		if (sprite.getPosition().x - bomb->position().x < bomb->radius() * GRID_SLOT_SIZE && abs(sprite.getPosition().y - bomb->position().y) <GRID_SLOT_SIZE && sprite.getPosition().x - bomb->position().x >0)
		{
			directions.erase(std::remove(directions.begin(), directions.end(), left), directions.end());
		}

		if (bomb->position().x - sprite.getPosition().x < bomb->radius() * GRID_SLOT_SIZE && abs(sprite.getPosition().y - bomb->position().y) < GRID_SLOT_SIZE && bomb->position().x - sprite.getPosition().x >0)
		{
			directions.erase(std::remove(directions.begin(), directions.end(), right), directions.end());
		}

		if (sprite.getPosition().y - bomb->position().y < bomb->radius() * GRID_SLOT_SIZE && abs(sprite.getPosition().x - bomb->position().x) < GRID_SLOT_SIZE && sprite.getPosition().y - bomb->position().y >0)
		{
			directions.erase(std::remove(directions.begin(), directions.end(), top), directions.end());
		}

		if (bomb->position().y - sprite.getPosition().y < bomb->radius() * GRID_SLOT_SIZE && abs(sprite.getPosition().x - bomb->position().x) < GRID_SLOT_SIZE && bomb->position().y - sprite.getPosition().y >0)
		{
			directions.erase(std::remove(directions.begin(), directions.end(), bottom), directions.end());
		}
	}

	for (auto player : players)
	{
		if (sprite.getPosition().x - player->get_position().x < 2 * GRID_SLOT_SIZE && abs(sprite.getPosition().y - player->get_position().y) < GRID_SLOT_SIZE/10 && sprite.getPosition().x - player->get_position().x > 0)
		{
			directions = add_direction_to_player_if_possible_(directions, left);
		}

		if (player->get_position().x - sprite.getPosition().x < 2 * GRID_SLOT_SIZE && abs(sprite.getPosition().y - player->get_position().y) < GRID_SLOT_SIZE/10 && player->get_position().x - sprite.getPosition().x > 0)
		{
			directions = add_direction_to_player_if_possible_(directions, right);
		}

		if (sprite.getPosition().y - player->get_position().y < 2 * GRID_SLOT_SIZE && abs(sprite.getPosition().x - player->get_position().x) < GRID_SLOT_SIZE/10 && sprite.getPosition().y - player->get_position().y > 0)
		{
			directions = add_direction_to_player_if_possible_(directions, top);
		}

		if (player->get_position().y - sprite.getPosition().y < 2 * GRID_SLOT_SIZE && abs(sprite.getPosition().x - player->get_position().x) < GRID_SLOT_SIZE/10 && player->get_position().y - sprite.getPosition().y > 0)
		{
			directions = add_direction_to_player_if_possible_(directions, bottom);
		}
	}
	return directions;
}

void Enemy::move(std::vector<std::shared_ptr<Wall>> walls, std::vector<std::shared_ptr<Bomb>> bombs, std::vector<std::shared_ptr<Player> > players)
{
	srand(time(NULL));
	// Movement is dependent on the type
	// More description about movement you can find here: https://gitlab-stud.elka.pw.edu.pl/dfokashc/proi-project/-/tree/main/Bomberman
	if (this->type == EnemyTypeMovement::RANDOM)
	{

		sf::Texture enemy_text;
		if (!enemy_text.loadFromFile(ENEMY_PATH)) throw TextureCanNotBeLoadedException(("Can't load texture for enemy!"));

		Enemy next_pos_enemy(this->get_position(), TEXTURE_SCALE, enemy_text);
		next_pos_enemy.sprite.move(sf::Vector2f(movement_direction.x * movement_speed, movement_direction.y * movement_speed));


		// if next position of enemy intersects other object or border of screen than intersects_already is true
		bool intersects_already = false;
		bool close_to_bomb = close_to_bobm_(bombs);
		bool close_to_player = close_to_player_(players);

		// After the start intersects_already should be true so that enemy can start to go
		if (firstMove)
		{
			intersects_already = true;
			firstMove = false;
		}
		for (int i = 0; i < walls.size(); i++)
		{
			if (walls[i].get()->get_global_bounds().intersects(next_pos_enemy.get_global_bounds()))
			{
				intersects_already = true;
				break;
			}
		}

		// if next position of enemy intersects object then change its direction
		if (intersects_already || close_to_bomb || close_to_player)
		{
			auto available_direction = get_available_directions(walls, bombs, players);
			if (available_direction.size() != 0)
			{
				int chosen_index = rand() % available_direction.size();
				this->movement_direction = available_direction[chosen_index].second;
			}
			else
			{
				movement_direction = { 0, 0 };
			}
		}
		this->sprite.move(sf::Vector2f(movement_direction.x * movement_speed, movement_direction.y * movement_speed));
	}
}

void Enemy::set_is_dead(bool new_value)
{
	is_dead_ = new_value;
}

bool Enemy::is_dead()
{
	return is_dead_;
}

bool Enemy::close_to_bobm_(std::vector<std::shared_ptr<Bomb>> bombs)
{
	for (auto bomb : bombs)
	{
		if (abs(sprite.getPosition().x - bomb->position().x) < GRID_SLOT_SIZE && abs(sprite.getPosition().y - bomb->position().y) < GRID_SLOT_SIZE)
		{
			return true;
		}
	}
	return false;
}

std::vector<std::pair<std::string, sf::Vector2i>> Enemy::add_direction_to_player_if_possible_(std::vector<std::pair<std::string, sf::Vector2i>> directions, std::pair<std::string, sf::Vector2i> possible_dir)
{
	for (auto direction : directions)
	{
		if (direction.first == possible_dir.first)
		{
			directions.push_back(possible_dir);
			directions.push_back(possible_dir);
			directions.push_back(possible_dir);
			directions.push_back(possible_dir);
			return directions;
		}
	}
	return directions;
}

bool Enemy::close_to_player_(std::vector<std::shared_ptr<Player>> players)
{
	for (auto player : players)
	{
		if ((abs(player->get_position().x - sprite.getPosition().x) < 2 * GRID_SLOT_SIZE && abs(player->get_position().y - sprite.getPosition().y) <  GRID_SLOT_SIZE/10) ||
			(abs(player->get_position().y - sprite.getPosition().y) < 2 * GRID_SLOT_SIZE && abs(player->get_position().x - sprite.getPosition().x) < GRID_SLOT_SIZE / 10))
		{
			return true;
		}
	}
	return false;
}
