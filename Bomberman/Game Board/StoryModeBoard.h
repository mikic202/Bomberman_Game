#ifndef StoryModeBoard_H
#define StoryModeBoard_H
#include "GameBoard.h"


class StoryModeBoard : public GameBoard
{
private:
	int dificulty_;
	sf::Sprite door_sprite_;
public:
	StoryModeBoard(int levels_pased);
	int dificulty() const;
	sf::Vector2f door_position() const;
	sf::FloatRect get_door_global_bounds();
};


#endif // !StoryModeBoard_H
