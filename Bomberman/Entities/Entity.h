#pragma once
#include <SFML/Graphics.hpp>
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
	//Entity(int pos_x, int pos_y, unsigned int size_x, unsigned int size_y, int speed);
	Entity(sf::Vector2f position, sf::Texture& texture, int speed = 5);
	Entity(sf::Vector2f position, sf::Texture& texture, sf::Vector2f size, int speed = 5);

	void move(Direction direction);

	void move(sf::Vector2f distance);

	void draw_to(sf::RenderWindow& window);

	//int get_position_x();
	//int get_position_y();
	sf::Vector2f get_position();
	int get_speed();
	sf::Vector2f get_size();

	//void set_position_x(int new_pos_x); 
	//void set_position_y(int new_pos_y);
	void set_position(sf::Vector2f position);

	void set_speed(int new_speed);

	sf::FloatRect get_global_bounds();

	void scale(sf::Vector2f size);

	virtual ~Entity();
protected:
	int speed;
	sf::Texture texture;
	sf::Sprite sprite;


	// size of sprite of entity
	unsigned int size_x, size_y;
};
