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
};


#endif // !MainMenu_H
