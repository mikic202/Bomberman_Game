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

std::vector<GameTypeEnum> Menu::open_menu(sf::RenderWindow& window)
{
	genarate_menu_();
	while (is_menu_open_)
	{
        check_quit_(window);
		check_actions_(window);
		draw_menu_(window);
	}
}

GameTypeEnum Menu::check_actions_(sf::RenderWindow& window)
{
	for (auto button_pair : buttons_)
	{
		if (button_pair.second.is_pressed(window))
		{
			return button_pair.first;
		}
	}
	return GameTypeEnum::no_choice;
}

