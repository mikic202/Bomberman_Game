//Miko�aj Chomanski

#ifndef Door_H
#define Door_H
#include "Explosion.h"
#include "../Consts.h"
#include"../Entities/Player/Player.h"


class Door : public Wall
{
private:
	std::string door_texture_path_ = DOOR_PATH;
public:
	Door() {};
	Door(sf::Vector2f position, sf::Vector2f scale);
	Door(sf::Vector2f position, sf::Vector2f scale, sf::Texture& wall_texture);
};


#endif
