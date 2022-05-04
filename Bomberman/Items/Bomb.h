#ifndef Bomb_H
#define Bomb_H
#include "Item.h"


class Bomb : public Item
{
private:
	int radius_;
	int delay_;
	int strength_;
public:
	Bomb() {};
	Bomb(std::vector<int> position, int radius, int delay, int strength);
	void set_radius(int new_radius);
	int radius();
	void set_delay(int new_delay);
	int delay();
	void set_strength(int new_strength);
	int strength();
};


#endif // !Bomb_H
