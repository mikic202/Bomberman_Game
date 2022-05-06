#ifndef Bomb_H
#define Bomb_H
#include "Item.h"
#include <chrono>


class Bomb : public Item
{
private:
	int radius_;
	int delay_;
	int strength_;
	std::chrono::time_point<std::chrono::steady_clock> placement_time_;
public:
	Bomb() {};
	Bomb(std::vector<int> position, int radius, int delay, int strength, sf::Vector2f scale, std::string image_path);
	void set_radius(int new_radius);
	int radius();
	void set_delay(int new_delay);
	int delay();
	void set_strength(int new_strength);
	int strength();
	bool did_blow();
};


#endif // !Bomb_H
