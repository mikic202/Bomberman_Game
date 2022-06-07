//Miko³aj Chomanski

#ifndef Bomb_H
#define Bomb_H
#include "Item.h"
#include <chrono>


class Bomb : public Item
{
private:
	int radius_ = 0;
	int delay_ = 0;
	int strength_ = 0;
	std::chrono::time_point<std::chrono::steady_clock> placement_time_;
	std::vector<int> position_on_board_;
	std::string texture_path_ = "Assets/Bomb.png";
public:
	Bomb() {};
	Bomb(sf::Vector2f position, int radius, int delay, int strength, sf::Vector2f scale);
	Bomb(sf::Vector2f position, int radius, int delay, int strength, sf::Vector2f scale, sf::Texture &bomb_texture);
	void set_radius(int new_radius);
	int radius();
	void set_delay(int new_delay);
	int delay();
	void set_strength(int new_strength);
	int strength();
	bool did_blow();
	std::vector<int> position_on_board();
};


#endif // !Bomb_H
