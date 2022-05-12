#ifndef Box_H
#define Box_H
#include "Wall.h"


class Box : public Wall	
{
private:
	int hits_to_brake_ = 1;
	bool chek_if_broken_();
	std::string box_texture_path_ = "Assets/Bomb.png"
public:
	Box() {  };
	Box(sf::Vector2f position, int hits_to_brake, sf::Vector2f scale, std::string image_path);
	void set_hits_to_brake(int new_hits);
	int hits_to_brake();
	bool hit(int strength);
};


#endif // !Box_H

