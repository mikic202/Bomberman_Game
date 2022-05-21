#include "Game.h"
#include <fstream>
#include <string>



void Game::play(int save_number, char type)
{
    play_story_(save_number);
}

void Game::play_story_(int save_number)
{
    sf::RenderWindow window(sf::VideoMode(1600, 700), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Bomb bomb({ 10, 10 }, 5, 6, 6, { 0.5, 0.5 });

    //sf::Sprite item_sprite_;
    //sf::Texture item_texture;

    VersusModeBoard board(20);
    StoryModeBoard story_b_(13, 1);

    std::cout << "a";
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                save_game_(save_number, 'S', story_b_.level_number(), points_);
                window.close();
            }
        }

        window.clear();
        story_b_.draw_to(window);
        //bomb.draw_to(window);
        //window.draw(bomb.item_sprite_);
        //window.draw(item_sprite_);
        //window.draw(shape);
        window.display();
    }

    return;
}

void Game::save_game_(int save_number, char type, int leve_number, int points)
{
    std::ofstream save_file;
    if (type == 'S')
    {
        save_file.open(STORY_SAVES.at(save_number));
    }
    else if (type == 'C')
    {
        save_file.open(CO_OP_SAVES.at(save_number));
    }
    save_file << leve_number;
    save_file << "\n";
    save_file << points;
    save_file.close();
}

std::vector<int> Game::load_game(int save_number, char type)
{
    std::string line;
    int level_number;
    std::ifstream save_file;
    if (type == 'S')
    {
        save_file.open(STORY_SAVES.at(save_number));
    }
    else if (type == 'C')
    {
        save_file.open(CO_OP_SAVES.at(save_number));
    }
    std::getline(save_file, line);
    level_number = std::stoi(line);
    std::getline(save_file, line);
    save_file.close();
    return std::vector<int> {level_number, std::stoi(line)};
}
