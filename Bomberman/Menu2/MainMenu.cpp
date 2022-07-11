#include "MainMenu.h"
#include "../Consts.h"


void MainMenu::genarate_menu_()
{
	buttons_.insert(std::pair<int, Button>(1, Button({ WINDOW_WIDTH / 2, 250.f }, 50, sf::Color::Yellow, "Play Story", font_)));
	buttons_.insert(std::pair<int, Button>(2, Button({ WINDOW_WIDTH / 2, 400.f }, 50, sf::Color::Yellow, "Play Cooperation", font_)));
	buttons_.insert(std::pair<int, Button>(3, Button({ WINDOW_WIDTH / 2, 560.f }, 50, sf::Color::Yellow, "Play Versus", font_)));
}

void MainMenu::draw_menu_(sf::RenderWindow& window)
{
	window.clear(sf::Color(69, 159, 66));
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
