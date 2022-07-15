#include "ChoseSaveMenu.h"

void ChoseSaveMenu::genarate_menu_()
{
    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::first_s, Button({ WINDOW_WIDTH / 2, 250.f }, 50, sf::Color::Yellow, "Save 1", font_)));
    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::second_s, Button({ WINDOW_WIDTH / 2, 400.f }, 50, sf::Color::Yellow, "Save 2", font_)));
    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::third_s, Button({ WINDOW_WIDTH / 2, 560.f }, 50, sf::Color::Yellow, "Save 3", font_)));
}

void ChoseSaveMenu::draw_menu_(sf::RenderWindow& window)
{
    window.clear(sf::Color(69, 159, 66));
    for (auto buttons : buttons_)
    {
        buttons.second.draw_to(window);
    }
    window.display();
}

ChoseSaveMenu::ChoseSaveMenu()
{
    if (!font_.loadFromFile(FONT_PATH))
    {
        throw(std::exception());
    }
    is_menu_open_ = true;
}

std::vector<GameTypeEnum> ChoseSaveMenu::open_menu(sf::RenderWindow& window)
{
    check_if_mouse_still_pressed_();
    GameTypeEnum chosen_save = GameTypeEnum::no_choice;
    genarate_menu_();
    while (is_menu_open_)
    {
        check_quit_(window);
        chosen_save = check_actions_(window);
        draw_menu_(window);
        if (chosen_save != GameTypeEnum::no_choice)
        {
            is_menu_open_ = false;
        }
    }
    return { chosen_save };
}
