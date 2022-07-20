#include "ChoseSaveMenu.h"

void ChoseSaveMenu::genarate_menu_()
{
    title_text_.setFont(font_);
    title_text_.setString("Chose Save");
    title_text_.setCharacterSize(70);
    title_text_.setFillColor(sf::Color::Yellow);
    auto center = title_text_.getLocalBounds().width / 2.f;
    title_text_.setOrigin({ center, title_text_.getGlobalBounds().top });
    title_text_.setPosition({ WINDOW_WIDTH / 2, 100.f });

    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::first_s, Button({ WINDOW_WIDTH / 6, 400.f }, 50, sf::Color::Yellow, "Save 1", font_)));
    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::second_s, Button({ 3*WINDOW_WIDTH / 6, 400.f }, 50, sf::Color::Yellow, "Save 2", font_)));
    buttons_.insert(std::pair<GameTypeEnum, Button>(GameTypeEnum::third_s, Button({ 5*WINDOW_WIDTH / 6, 400.f }, 50, sf::Color::Yellow, "Save 3", font_)));
}

void ChoseSaveMenu::draw_menu_(sf::RenderWindow& window)
{
    window.clear(sf::Color(69, 159, 66));
    window.draw(title_text_);
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
