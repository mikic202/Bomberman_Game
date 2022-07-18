#include "PauseMenu.h"
#include <iostream>

void PauseMenu::genarate_menu_()
{
    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::restart, Button({ WINDOW_WIDTH / 2, 250.f }, 50, sf::Color::Yellow, "Continue", font_)));
    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::new_game, Button({ WINDOW_WIDTH / 2, 400.f }, 50, sf::Color::Yellow, "New Game", font_)));
    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::exit, Button({ WINDOW_WIDTH / 2, 560.f }, 50, sf::Color::Yellow, "Exit", font_)));
}

void PauseMenu::draw_menu_(sf::RenderWindow& window)
{
    window.clear(sf::Color(69, 159, 66));
    for (auto button : buttons_)
    {
        button.second.draw_to(window);
    }
    window.display();
}

PauseMenu::PauseMenu()
{
	is_menu_open_ = true;
    if (!font_.loadFromFile(FONT_PATH))
    {
        throw(std::exception());
    }
}

std::vector<GameTypeEnum> PauseMenu::open_menu(sf::RenderWindow& window)
{
    check_if_mouse_still_pressed_();
    GameTypeEnum choice = GameTypeEnum ::no_choice;
    genarate_menu_();
    while (is_menu_open_)
    {
        check_quit_(window);
        choice = check_actions_(window);
        draw_menu_(window);
        if (choice != GameTypeEnum::no_choice)
        {
            is_menu_open_ = false;
            std::cout << "a";
        }
    }
    if (choice == GameTypeEnum::exit)
    {
        window.close();
        exit(1);

    }
    return { choice };
}
