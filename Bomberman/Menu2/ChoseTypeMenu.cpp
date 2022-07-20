#include "ChoseTypeMenu.h"
#include "ChoseSaveMenu.h"

void ChoseTypeMenu::genarate_menu_()
{
    title_text_.setFont(font_);
    title_text_.setString("Chose type");
    title_text_.setCharacterSize(70);
    title_text_.setFillColor(sf::Color::Yellow);
    auto center = title_text_.getLocalBounds().width / 2.f;
    title_text_.setOrigin({ center, title_text_.getGlobalBounds().top });
    title_text_.setPosition({ WINDOW_WIDTH / 2, 100.f });

    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::new_game, Button({ WINDOW_WIDTH / 4, 350.f }, 50, sf::Color::Yellow, "New Game", font_)));
    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::open_save, Button({ 3*WINDOW_WIDTH / 4, 350.f }, 50, sf::Color::Yellow, "Open Save", font_)));
}

void ChoseTypeMenu::draw_menu_(sf::RenderWindow& window)
{
    window.clear(sf::Color(69, 159, 66));
    window.draw(title_text_);
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
