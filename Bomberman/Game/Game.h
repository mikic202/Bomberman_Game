#ifndef Game_H
#define Game_H
#include <SFML/Graphics.hpp>
#include"../Items/Bomb.h"
#include "../Game Board/StoryModeBoard.h"
#include "../Game Board/VersusModeBoard.h"
#include "../Items/Box.h"
#include "../Entities/Player/Player.h"
#include"../Entities/Enemy/Enemy.h"


class Game
{
private:
	int pixels_moved_;
	std::shared_ptr<GameBoard> game_board_;
	int points_ = 1;
	std::vector<std::shared_ptr<Player> > players_;
	sf::Texture player1_texture_;
	sf::Texture player2_texture_;
	sf::Texture door_texture_;
	sf::Texture bomb_texture_;
	sf::Texture wall_texture_;
	sf::Texture box_texture_;
	sf::Texture explosion_texture_; // all of the textures had to be in the game class because for some reason sfml texturees dont work in smart pointers
	std::vector<std::shared_ptr<Bomb> > bombs_on_b_;
	std::vector<int> is_player_stationary_ = { 0, 0 };
	std::vector<std::shared_ptr<Explosion> > explosions_;
	std::vector<Enemy> enemies_;
	int explosions_on_board_ = 0;
	void play_story_(int save_number, bool new_game, sf::RenderWindow &window, int number_of_players);
	void play_coop_();
	void play_versus_(sf::RenderWindow& window);
	void move_players_(sf::RenderWindow& window, bool versus = false);
	void place_bombs_(std::shared_ptr< Player> player, sf::Keyboard::Key bomb_placing, int pixels_moved);
	bool check_if_colides_left_(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	bool check_if_colides_right_(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	void check_if_colides_up_(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	void check_if_colides_down_(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window);
	void save_game_(int save_number, char type, int leve_number, int points);
	std::vector<int> load_game_(int save_number, char type);
	bool is_player_close_to_edge_(std::shared_ptr< Player> player, sf::RenderWindow &window);
	void create_players_(int player_number, bool versus_mode = false, int board_size = 0);
	bool detect_player_door_colision_(const sf::FloatRect& door_bounds);
	void bobm_explosion_(std::vector<std::shared_ptr<Wall> > items_on_b);
	void place_explosion_(std::vector<std::shared_ptr<Wall> > items_on_b, std::shared_ptr<Bomb> bomb);
	void check_where_explosion_stops_(std::vector<std::shared_ptr<Wall> > items_on_b, std::shared_ptr<Bomb> bomb);
	bool check_explosion_();
	bool kill_players_(int pixels_moved);
	bool check_enemies_();
	void display_player_move_sideways(std::shared_ptr< Player> player, int multiplier);
	void display_player_move_forward(std::shared_ptr< Player> player);
	void display_player_move_backward(std::shared_ptr< Player> player);
	void generate_enemies();
	void shift_game_board_(float distance, int player_num);
	bool can_gameboard_be_shifter_(bool right,  sf::RenderWindow& window);
	//void draw_elements_of_game_(sf::RenderWindow& window);
public:
	Game() {};
	void play(int save_number, char type, bool new_game, sf::RenderWindow &window);
};


#endif // !Game_H

