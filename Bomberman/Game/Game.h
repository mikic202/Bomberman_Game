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
	void play_story_(int save_number);
	void play_coop_();
	void play_versus_();
	void move_player_();
	void save_game_(int save_number, char type);
	int load_game();
public:
	Game() {};
	void play(int save_number, char type);
};


#endif // !Game_H

