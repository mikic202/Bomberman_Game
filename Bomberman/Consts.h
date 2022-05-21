#ifndef Consts_H
#define Consts_H
#include <vector>
#include <map>


const int DIMENSIONS = 2;
const std::vector<int> MAX_SIZE = { 1000, 1000 };
const int MAX_EXPLOSION_DELAY = 10;

const int GRID_SLOT_SIZE = 50;

const std::string BOMB_PATH = "Assets/Bomb.png";
const std::string WALL_PATH = "Assets/Wall.png";
const std::string BOX_PATH = "Assets/Box.png";
const std::string DOOR_PATH = "Assets/Bomb.png";

const std::map<int, std::string> STORY_SAVES = { {1, "Story1.txt"}, {2, "Story2.txt"} , {3, "Story3.txt"} };
const std::map<int, std::string> CO_OP_SAVES = { {1, "Co-op1.txt"}, {2, "Co-op2.txt"} , {3, "Co-op3.txt"} };



#endif // !Consts_H

