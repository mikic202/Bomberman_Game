#include "Player.h"

//Player::Player(int pos_x, int pos_y, unsigned int size_x, unsigned int size_y, int speed, int hp, unsigned int quantity_bombs) : Entity(pos_x, pos_y, size_x, size_y, speed) {
//	this->hp = hp;
//	this->quantity_bombs = quantity_bombs;
//}



Player::Player(sf::Vector2f position, sf::Texture& texture, sf::Vector2f size, unsigned int quantity_bombs, int speed, int hp)
{
	this->sprite = sf::Sprite(texture);
	this->sprite.setPosition(position);
	this->sprite.scale(size);
	this->quantity_bombs = quantity_bombs;
	this->hp = hp;
	
}

int Player::get_hp(){
	return hp;
}

int Player::get_quanity_bombs(){
	return quantity_bombs;
}

void Player::set_last_texture_number(int new_last_texture_number)
{
	this->last_texture_number = new_last_texture_number;
}

int Player::get_last_texture_number()
{
	return this->last_texture_number;
}

void Player::set_hp(int new_hp){
	this->hp = new_hp;
}

void Player::set_quanity_bombs(int new_quanity_bombs){
	this->quantity_bombs = new_quanity_bombs;
}

bool Player::on_bomb(std::vector<std::shared_ptr<Bomb>> bombs)
{
	// Get relative position on grid
	sf::Vector2f player_pos = this->get_position();

	//sf::Vector2u player_grid_pos(int(this->get_position().x / GRID_SLOT_SIZE), int(this->get_position().y / GRID_SLOT_SIZE));



	for (auto& bomb : bombs)
	{
		//sf::Vector2u bomb_grid_pos(int(bomb.get()->position().x / GRID_SLOT_SIZE), int(bomb.get()->position().y / GRID_SLOT_SIZE));

		//if (bomb_grid_pos == player_grid_pos)
			//return true;

		if(bomb.get()->item_sprite().getGlobalBounds().intersects(this->sprite.getGlobalBounds()))
			return true;
	}
	return false;
}


bool Player::can_textured_be_placed(int time_milliseconds)
{
	return(time_milliseconds < std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - time_since_texture_changed).count());
}

void Player::place_texture()
{
	this->time_since_texture_changed = std::chrono::steady_clock::now();
}
