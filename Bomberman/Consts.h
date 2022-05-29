#ifndef Consts_H
#define Consts_H
#include <vector>
#include <map>


const int DIMENSIONS = 2;
const std::vector<int> MAX_SIZE = { 1000, 1000 };
const int MAX_EXPLOSION_DELAY = 3;
const int NUMBER_OF_WALLS_Y = 11;

const int PLAYER_LIVES = 3;

const int GRID_SLOT_SIZE = 75;
const sf::Vector2f TEXTURE_SCALE = { .214286, .214286 };

const std::vector < std::vector<sf::Keyboard::Key> > PLAYERS_KEYS = { 
				{sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::A, sf::Keyboard::Space}, 
				{sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Right, sf::Keyboard::Left, sf::Keyboard::Enter} };

const std::string BOMB_PATH = "Assets/Bomb.png";
const std::string WALL_PATH = "Assets/Wall.png";
const std::string BOX_PATH = "Assets/Box.png";
const std::string DOOR_PATH = "Assets/Door.png";
const std::string PLAYER_PATH = "Assets/Player.png";
const std::string ENEMY_PATH = "Assets/Enemy.png";
const std::string FONT_PATH = "Assets/Fonts/Pixeboy.ttf";
const std::string EXPLOSION_PATH = "Assets/Explosion.png";
const std::vector<std::string> PLAYER_MOVE_FORWARD{ "Assets/Player_move_f1.png", "Assets/Player_move_f2.png"};
const std::vector<float> PLAYER_TEXTURE_SIZE = { 113 * TEXTURE_SCALE.x, 253 * TEXTURE_SCALE.y };

const int BOMB_PLACEMENT_TOLERANCES = 5;

const std::map<int, std::string> STORY_SAVES = { {1, "Game Saves/Story1.txt"}, {2, "Game Saves/Story2.txt"} , {3, "Game Saves/Story3.txt"} };
const std::map<int, std::string> CO_OP_SAVES = { {1, "Game Saves/Co-op1.txt"}, {2, "Game Saves/Co-op2.txt"} , {3, "Game Saves/Co-op3.txt"} };



#endif // !Consts_H

