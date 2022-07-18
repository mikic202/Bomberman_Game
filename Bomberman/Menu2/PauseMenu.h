#ifndef PauseMenu_H
#define PauseMenu_H
#include "Menu.h"


class PauseMenu : Menu
{
private:
	void genarate_menu_();
	void draw_menu_(sf::RenderWindow& window);
public:
	PauseMenu();
	std::vector<GameTypeEnum> open_menu(sf::RenderWindow& window);
};


#endif // !PauseMenu_H

