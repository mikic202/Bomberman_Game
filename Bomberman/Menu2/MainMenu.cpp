#include "MainMenu.h"
#include "../Consts.h"


void MainMenu::genarate_menu_()
{
	buttons_.insert(std::pair<int, Button>(1, Button({ 100.f, WINDOW_HEIGHT / 2 }, 20, sf::Color::Yellow, "Play Story")));
	buttons_.insert(std::pair<int, Button>(2, Button({ 100.f, WINDOW_HEIGHT / 2 }, 20, sf::Color::Yellow, "Play Cooperation")));
	buttons_.insert(std::pair<int, Button>(3, Button({ 100.f, WINDOW_HEIGHT / 2 }, 20, sf::Color::Yellow, "Play Versus")));
}

void MainMenu::draw_menu_(sf::RenderWindow& window)
{
	window.clear(sf::Color::Green);
	for (auto buttons : buttons_)
	{
		buttons.second.draw_to(window);
	}
}
