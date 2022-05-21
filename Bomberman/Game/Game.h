#ifndef Game_H
#define Game_H
#include <SFML/Graphics.hpp>
#include"../Items/Bomb.h"
#include "../Game Board/StoryModeBoard.h"
#include "../Game Board/VersusModeBoard.h"
#include "../Items/Box.h"


class Game
{
private:
	sf::RenderWindow window_;
	int points_ = 1;
	void play_story_(int save_number, bool new_game);
	void play_coop_();
	void play_versus_();
	void move_player_(Player2 &player);
	void save_game_(int save_number, char type, int leve_number, int points);
	std::vector<int> load_game(int save_number, char type);
public:
	Game() {};
	void play(int save_number, char type, bool new_game);
};


class Player2
{
public:
    Player2(sf::Vector2f size)
    {
        player.setSize(size);
        player.setFillColor(sf::Color::Green);
    }

    void draw_to(sf::RenderWindow& window)
    {
        window.draw(player);
    }
    void move(sf::Vector2f distance)
    {
        player.move(distance);
    }
    void set_position(sf::Vector2f position)
    {
        player.setPosition(position);
    }

    int getX() {
        return player.getPosition().x;
    }

    int getY() {
        return player.getPosition().y;
    }

private:
    sf::RectangleShape player;
};


#endif // !Game_H

