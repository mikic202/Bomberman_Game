#pragma once
// Pure abstract class that describes
// object that can be displayed and move

enum class Direction
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};
class Entity 
{
public:
	Entity();
	Entity(int pos_x, int pos_y, unsigned int size_x, unsigned int size_y, int speed); 

	void move(Direction direction);

	int get_position_x();
	int get_position_y();
	int get_speed();

	void set_position_x(int new_pos_x); 
	void set_position_y(int new_pos_y);
	void set_speed(int new_speed);

	virtual ~Entity() = 0;
private:
	int speed;
	int pos_x, pos_y;

	// size of sprite of entity
	unsigned int size_x, size_y;
};
