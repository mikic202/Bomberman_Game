#ifndef Consts_H
#define Consts_H
#include <vector>
#include <map>


const int DIMENSIONS = 2;
const std::vector<int> MAX_SIZE = { 1000, 1000 };
const int MAX_EXPLOSION_DELAY = 10;
const int PLAYER_LIVES = 3;

const int WINDOW_WIDTH = 1080;
const int WINDOW_HEIGHT = 800;


const int GRID_SLOT_SIZE = 50;
const sf::Vector2f TEXTURE_SCALE = { .14286, .14286 };

const sf::Color MAIN_MENU_TEXT_COLOR = sf::Color(255, 160, 35, 255);
const sf::Color MAIN_MENU_TEXT_TARGET_COLOR = sf::Color(255, 0, 0, 255);

const sf::Color CREDITS_MENU_TEXT_COLOR = sf::Color(200, 255, 1, 255);

// Seconds needed to make "cooldown" for pressing other option in menu 
const float MENU_CHANGE_FIELD_COOLDOWN_SECONDS = 0.2;

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
const std::vector<float> PLAYER_TEXTURE_SIZE = { 113 * TEXTURE_SCALE.x, 253 * TEXTURE_SCALE.y };

const int BOMB_PLACEMENT_TOLERANCES = 5;

const std::map<int, std::string> STORY_SAVES = { {1, "Game Saves/Story1.txt"}, {2, "Game Saves/Story2.txt"} , {3, "Game Saves/Story3.txt"} };
const std::map<int, std::string> CO_OP_SAVES = { {1, "Game Saves/Co-op1.txt"}, {2, "Game Saves/Co-op2.txt"} , {3, "Game Saves/Co-op3.txt"} };



#endif // !Consts_H

