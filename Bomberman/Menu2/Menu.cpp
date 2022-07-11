#include "Menu.h"


void Menu::check_quit_(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            is_menu_open_ = false;
            window.close();
            exit(1);
        }
    }
}

void Menu::open_menu(sf::RenderWindow& window)
{
	genarate_menu_();
	while (is_menu_open_)
	{
        check_quit_(window);
		check_actions_(window);
		draw_menu_(window);
	}
}

