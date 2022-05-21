#ifndef Game_H
#define Game_H
#include <SFML/Graphics.hpp>
#include"../Items/Bomb.h"
#include "../Game Board/StoryModeBoard.h"
#include "../Game Board/VersusModeBoard.h"
#include "../Items/Box.h"
#include "../Player2.h"


class Game
{
private:
	sf::RenderWindow window_;
	int points_ = 1;
	void play_story_(int save_number, bool new_game);
	void play_coop_();
	void play_versus_();
	void move_player_(Player2 &player, std::vector<std::shared_ptr<Wall> > items_on_b);
    void check_if_player_stops_(Player2& player, std::vector<std::shared_ptr<Wall> > items_on_b);
	void save_game_(int save_number, char type, int leve_number, int points);
	std::vector<int> load_game(int save_number, char type);
public:
	Game() {};
	void play(int save_number, char type, bool new_game);
};


#endif // !Game_H

