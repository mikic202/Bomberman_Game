#include "Menu.h"


void Menu::open_menu()
{
	while (is_menu_open_)
	{
		check_buttons_();
		draw_menu();
	}
}

