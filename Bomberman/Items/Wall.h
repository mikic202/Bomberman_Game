#ifndef Wall_H
#define Wall_H
#include "Item.h"


class Wall : public Item
{
public:
	sf::FloatRect get_global_bounds();
};


#endif // !Wall_H

