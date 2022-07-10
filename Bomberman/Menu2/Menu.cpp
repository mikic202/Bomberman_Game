#include "Menu.h"


void Menu::open_menu(sf::RenderWindow& window)
{
	genarate_menu_();
	while (is_menu_open_)
	{
		check_buttons_(window);
		draw_menu_(window);
	}
}

