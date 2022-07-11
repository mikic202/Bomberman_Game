#include "MainMenu.h"
#include "../Consts.h"


void MainMenu::genarate_menu_()
{
	buttons_.insert(std::pair<int, Button>(1, Button({ WINDOW_WIDTH / 2, 200.f }, 20, sf::Color::Yellow, "Play Story", font_)));
	buttons_.insert(std::pair<int, Button>(2, Button({ WINDOW_WIDTH / 2, 300.f }, 20, sf::Color::Yellow, "Play Cooperation", font_)));
	buttons_.insert(std::pair<int, Button>(3, Button({ WINDOW_WIDTH / 2, 400.f }, 20, sf::Color::Yellow, "Play Versus", font_)));
}

void MainMenu::draw_menu_(sf::RenderWindow& window)
{
	window.clear(sf::Color::Green);
	for (auto buttons : buttons_)
	{
		buttons.second.draw_to(window);
	}
	window.display();
}

MainMenu::MainMenu()
{
	if (!font_.loadFromFile(FONT_PATH))
	{
		throw(std::exception());
	}
	is_menu_open_ = true;
}
