#ifndef MainMenu_H
#define MainMenu_H
#include "Menu.h"


class MainMenu : public Menu
{
private:
	void genarate_menu_();
	void draw_menu_(sf::RenderWindow& window);
public:
	MainMenu();
	std::vector<GameTypeEnum> open_menu(sf::RenderWindow& window);
};


#endif // !MainMenu_H
