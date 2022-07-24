#pragma once
#include <SFML/Graphics.hpp>

enum class Direction
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};

// Pure abstract class that describes
// object that can be displayed and move
class Entity 
{
public:
	Entity();
	Entity(sf::Vector2f position, sf::Texture& texture, int speed = 5);
	Entity(sf::Vector2f position, sf::Texture& texture, sf::Vector2f size, int speed = 5);

	void move(Direction direction);

	void move(sf::Vector2f distance);

	void draw_to(sf::RenderWindow& window);

	sf::Vector2f get_position();
	int get_speed();
	sf::Vector2f get_size();

	void set_position(sf::Vector2f position);

	void set_speed(int new_speed);

	sf::FloatRect get_global_bounds();

	void scale(sf::Vector2f size);

	virtual ~Entity() = 0;

	sf::FloatRect get_local_bounds();
protected:
	int speed;
	sf::Texture texture;
	sf::Sprite sprite;


	// size of sprite of entity
	unsigned int size_x, size_y;
};
