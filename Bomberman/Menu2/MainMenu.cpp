#include "MainMenu.h"
#include "../Consts.h"
#include "ChoseTypeMenu.h"
#include "../Game/Game.h"


void MainMenu::genarate_menu_()
{
	title_text_.setFont(font_);
	title_text_.setString("Bomberman");
	title_text_.setCharacterSize(70);
	title_text_.setFillColor(sf::Color::Yellow);
	auto center = title_text_.getLocalBounds().width / 2.f;
	title_text_.setOrigin({ center, title_text_.getGlobalBounds().top });
	title_text_.setPosition({ WINDOW_WIDTH / 2, 100.f });

	buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::story, Button({ WINDOW_WIDTH / 2, 300.f }, 50, sf::Color::Yellow, "Play Story", font_)));
	buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::coop, Button({ WINDOW_WIDTH / 2, 450.f }, 50, sf::Color::Yellow, "Play Cooperation", font_)));
	buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::versus, Button({ WINDOW_WIDTH / 2, 600.f }, 50, sf::Color::Yellow, "Play Versus", font_)));
}

void MainMenu::draw_menu_(sf::RenderWindow& window)
{
	window.clear(sf::Color(69, 159, 66));
	window.draw(title_text_);
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
				save_number = 3;
				break;
			}
			Game game;
			game.play(save_number, chosen_mode, return_choices[0], window);
		}
	}
	return std::vector<GameTypeEnum>();
}

