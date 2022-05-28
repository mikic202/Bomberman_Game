#ifndef Game_H
#define Game_H
#include <SFML/Graphics.hpp>
#include"../Items/Bomb.h"
#include "../Game Board/StoryModeBoard.h"
#include "../Game Board/VersusModeBoard.h"
#include "../Items/Box.h"
#include "../Entities/Player/Player.h"


class Game
{
private:
	std::shared_ptr<GameBoard> game_board_;
	int points_ = 1;
	std::vector<std::shared_ptr<Player> > players_;
	sf::Texture player1_texture_;
	sf::Texture player2_texture_;
	std::vector<std::shared_ptr<Bomb> > bombs_on_b_;
	std::vector<std::shared_ptr<Explosion> > explosions_;
	sf::Texture bomb_texture_;
	sf::Texture explosion_texture_;
	int explosions_on_board_ = 0;
	void play_story_(int save_number, bool new_game, sf::RenderWindow &window, int number_of_players);
	void play_coop_();
	void play_versus_(sf::RenderWindow& window);
	void move_player_(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window, std::vector<sf::Keyboard::Key> keys, int pixels_moved=0, bool versus = false);
	void place_bombs_(std::shared_ptr< Player> player, sf::Keyboard::Key bomb_placing);
	void check_if_colides_left(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	void check_if_colides_right(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	void check_if_colides_up(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	void check_if_colides_down(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	void save_game_(int save_number, char type, int leve_number, int points);
	std::vector<int> load_game(int save_number, char type);
	bool is_player_close_to_edge(std::shared_ptr< Player> player, sf::RenderWindow &window);
	void create_players_(int player_number, bool versus_mode = false, int board_size = 0);
	bool detect_player_door_colision(const sf::FloatRect& door_bounds);
	void bobm_explosion_(std::vector<std::shared_ptr<Wall> > items_on_b);
	void place_explosion_(std::vector<std::shared_ptr<Wall> > items_on_b, std::shared_ptr<Bomb> bomb);
	void check_where_explosion_stops(std::vector<std::shared_ptr<Wall> > items_on_b, std::shared_ptr<Bomb> bomb);
	//void draw_elements_of_game_(sf::RenderWindow& window);
public:
	Game() {};
	void play(int save_number, char type, bool new_game, sf::RenderWindow &window);
};


#endif // !Game_H

