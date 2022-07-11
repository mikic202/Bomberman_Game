#include "MainMenu.h"
#include "../Consts.h"
#include "ChoseTypeMenu.h"
#include "../Game/Game.h"


void MainMenu::genarate_menu_()
{
	buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::story, Button({ WINDOW_WIDTH / 2, 250.f }, 50, sf::Color::Yellow, "Play Story", font_)));
	buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::coop, Button({ WINDOW_WIDTH / 2, 400.f }, 50, sf::Color::Yellow, "Play Cooperation", font_)));
	buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::versus, Button({ WINDOW_WIDTH / 2, 560.f }, 50, sf::Color::Yellow, "Play Versus", font_)));
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

GameTypeEnum MainMenu::check_actions_(sf::RenderWindow& window)
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

MainMenu::MainMenu()
{
	if (!font_.loadFromFile(FONT_PATH))
	{
		throw(std::exception());
	}
	is_menu_open_ = true;
}

std::vector<GameTypeEnum> MainMenu::open_menu(sf::RenderWindow& window)
{
	genarate_menu_();
	while (is_menu_open_)
	{
		draw_menu_(window);
		check_quit_(window);
		GameTypeEnum chosen_mode = check_actions_(window);
		if (chosen_mode != GameTypeEnum::no_choice)
		{
			std::vector<GameTypeEnum> return_choices = { GameTypeEnum::no_choice, GameTypeEnum::no_choice };
			ChoseTypeMenu type_menu;
			switch (chosen_mode)
			{
			case GameTypeEnum::story:
				return_choices = type_menu.open_menu(window);
				break;
			case GameTypeEnum::coop:
				return_choices = type_menu.open_menu(window);
				break;
			case GameTypeEnum::versus:
				break;
			};
			int save_number = 1;

			switch (return_choices[1])
			{
			case GameTypeEnum::second_s:
				save_number = 2;
				break;
			case GameTypeEnum::third_s:
				save_number = 2;
				break;
			}
			Game game;
			game.play(save_number, chosen_mode, return_choices[0], window);
		}
	}
	return std::vector<GameTypeEnum>();
}

