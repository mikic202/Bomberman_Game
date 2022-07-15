#ifndef ChoseSaveMenu_H
#define ChoseSaveMenu_H
#include "Menu.h"


class ChoseSaveMenu : public Menu
{
private:
	void genarate_menu_();
	void draw_menu_(sf::RenderWindow& window);
public:
	ChoseSaveMenu();
	std::vector<GameTypeEnum> open_menu(sf::RenderWindow& window);
};


#endif // !ChoseSaveMenu_H

