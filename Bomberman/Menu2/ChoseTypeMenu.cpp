#include "ChoseTypeMenu.h"
#include "ChoseSaveMenu.h"

void ChoseTypeMenu::genarate_menu_()
{
    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::new_game, Button({ WINDOW_WIDTH / 2, 250.f }, 50, sf::Color::Yellow, "New Game", font_)));
    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::open_save, Button({ WINDOW_WIDTH / 2, 400.f }, 50, sf::Color::Yellow, "Open Save", font_)));
}

void ChoseTypeMenu::draw_menu_(sf::RenderWindow& window)
{
    window.clear(sf::Color(69, 159, 66));
    for (auto buttons : buttons_)
    {
        buttons.second.draw_to(window);
    }
    window.display();
}

ChoseTypeMenu::ChoseTypeMenu()
{
    if (!font_.loadFromFile(FONT_PATH))
    {
        throw(std::exception());
    }
    is_menu_open_ = true;
}

std::vector<GameTypeEnum> ChoseTypeMenu::open_menu(sf::RenderWindow& window)
{
    check_if_mouse_still_pressed_();
    GameTypeEnum chosen_mode;
    std::vector<GameTypeEnum> chose_save;
    genarate_menu_();
    while (is_menu_open_)
    {
        check_quit_(window);
        chosen_mode = check_actions_(window);
        draw_menu_(window);
        if (chosen_mode != GameTypeEnum::no_choice)
        {
            ChoseSaveMenu save_menu;
            chose_save = save_menu.open_menu(window);
            is_menu_open_ = false;
        }
    }
    return { chosen_mode, chose_save[0]};
}
