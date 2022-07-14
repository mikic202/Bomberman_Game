#ifndef ChoseTypeMenu_H
#define ChoseTypeMenu_H
#include "Menu.h"
#include <iostream>


class ChoseTypeMenu : public Menu
{
private:
	void genarate_menu_();
	void draw_menu_(sf::RenderWindow& window);
public:
	ChoseTypeMenu();
	std::vector<GameTypeEnum> open_menu(sf::RenderWindow& window);
};


#endif // !ChoseTypeMenu_H
