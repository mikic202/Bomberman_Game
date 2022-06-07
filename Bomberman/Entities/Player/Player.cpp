#include "Player.h"

Player::Player(sf::Vector2f position, sf::Texture& texture, sf::Vector2f size, unsigned int quantity_bombs, int speed, int hp)
{
	this->sprite = sf::Sprite(texture);
	this->sprite.setPosition(position);
	this->sprite.scale(size);
	this->quantity_bombs = quantity_bombs;
	this->hp = hp;
	
}

int Player::get_hp() { return hp; } 

int Player::get_quanity_bombs() { return quantity_bombs; }

void Player::set_last_texture_number(int new_last_texture_number) { this->last_texture_number = new_last_texture_number; }

int Player::get_last_texture_number() { return this->last_texture_number; }

void Player::set_hp(int new_hp) { this->hp = new_hp; }

void Player::set_quanity_bombs(int new_quanity_bombs) { this->quantity_bombs = new_quanity_bombs; }

bool Player::on_bomb(std::vector<std::shared_ptr<Bomb>> bombs)
{
	sf::Vector2f player_pos = this->get_position();

	for (auto& bomb : bombs)
	{
		if(bomb.get()->item_sprite().getGlobalBounds().intersects(this->sprite.getGlobalBounds()))
			return true;
	}
	return false;
}

// Function for changing texture for sprite
bool Player::can_textured_be_placed(int time_milliseconds)
{
	return(time_milliseconds < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - time_since_texture_changed).count());
}


void Player::place_texture() { this->time_since_texture_changed = std::chrono::steady_clock::now(); }
