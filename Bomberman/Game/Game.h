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
	std::vector<std::shared_ptr<Bomb> > bombs_on_b_;
	sf::Texture bomb_texture_;
	void play_story_(int save_number, bool new_game, sf::RenderWindow &window, int number_of_players);
	void play_coop_();
	void play_versus_();
	void move_player_(std::shared_ptr< Player2> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	void place_bombs_(std::shared_ptr< Player2> player);
	void check_if_colides_left(std::shared_ptr< Player2> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	void check_if_colides_right(std::shared_ptr< Player2> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	void check_if_colides_up(std::shared_ptr< Player2> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	void check_if_colides_down(std::shared_ptr< Player2> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	void save_game_(int save_number, char type, int leve_number, int points);
	std::vector<int> load_game(int save_number, char type);
	bool is_player_close_to_edge(std::shared_ptr< Player2> player, sf::RenderWindow &window);
	std::vector<std::shared_ptr<Player2> > create_players_(int player_number, sf::Texture& player_texture, bool versus_mode = false);
	//void draw_elements_of_game_(sf::RenderWindow& window);
public:
	Game() {};
	void play(int save_number, char type, bool new_game, sf::RenderWindow &window);
};


#endif // !Game_H

