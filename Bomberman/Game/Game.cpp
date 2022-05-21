#include "Game.h"
#include <fstream>
#include <string>



void Game::play(int save_number, char type, bool new_game)
{
    play_story_(save_number, new_game);
}

void Game::play_story_(int save_number, bool new_game)
{
    bool board_drawn = false;

    int level_number = 1;
    sf::RenderWindow window(sf::VideoMode(1600, 700), "SFML works!");
    window.setFramerateLimit(60);
    if (new_game)
    {
        std::vector<int> game_info = load_game(save_number, 'S');
        level_number = game_info[0];
        points_ = game_info[1];
    }

    StoryModeBoard story_b_(level_number, 1);
    Player2 player({ GRID_SLOT_SIZE / 2, GRID_SLOT_SIZE });
    player.set_position({ GRID_SLOT_SIZE, GRID_SLOT_SIZE });

    sf::Clock Clock;
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
        move_player_(player);
        window.clear();
        story_b_.draw_to(window);
        player.draw_to(window);
        window.display();
        /*std::cout << 1.f/Clock.getElapsedTime().asSeconds()<<"\n";
        Clock.restart();*/
    }

    return;
}


void Game::move_player_(Player2& player)
{
    const int MOVEMNT_SPEED = 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player.move({ 0, -MOVEMNT_SPEED });
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        player.move({ 0, MOVEMNT_SPEED });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.move({ MOVEMNT_SPEED, 0 });
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.move({ - MOVEMNT_SPEED, 0 });
    }
}

void Game::check_if_player_stops(Player2& player, std::vector<std::shared_ptr<Wall> > items_on_b)
{
    for (auto a : items_on_b)
    {
        /*if (a->is_coloding_player(player))
        {
            std::cout << "a";
        }*/
    }
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

