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
    player.set_position({ 0, 0 });

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
        //if(not sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        //    check_if_player_stops_(player, story_b_.items());
        move_player_(player, story_b_.items());
        window.clear();
        story_b_.draw_to(window);
        player.draw_to(window);
        window.display();
        /*std::cout << 1.f/Clock.getElapsedTime().asSeconds()<<"\n";
        Clock.restart();*/
    }

    return;
}


void Game::move_player_(Player2& player , std::vector<std::shared_ptr<Wall> > items_on_b)
{
    const int MOVEMNT_SPEED = 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player.move({ 0, -MOVEMNT_SPEED });
        check_if_player_stops_(player, items_on_b);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        player.move({ 0, MOVEMNT_SPEED });
        check_if_player_stops_(player, items_on_b);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.move({ MOVEMNT_SPEED, 0 });
        check_if_player_stops_(player, items_on_b);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.move({ - MOVEMNT_SPEED, 0 });
        check_if_player_stops_(player, items_on_b);
    }
}

void Game::check_if_player_stops_(Player2& player, std::vector<std::shared_ptr<Wall> > items_on_b)
{
    float player_s_x = player.size().x;
    float player_s_y = player.size().y;
    float player_x = player.getX();
    float player_y = player.getY();
    float item_x;
    float item_y;
    for (auto a : items_on_b)
    {
        if (a->is_coloding_player(player))
        {
            item_x = a->position().x;
            item_y = a->position().y;;
            if (player_x >= item_x - player_s_x && player_x <= item_x - player_s_x/2 && std::abs(item_y - player_y) < player_s_y - 5) 
                player.set_position({ item_x - player_s_x, player_y });
            else if (player_x <= item_x + GRID_SLOT_SIZE && std::abs(item_y - player_y) < player_s_y - 5) 
                player.set_position({ item_x + GRID_SLOT_SIZE, player_y });
            if (player_y <= item_y + player_s_y && player_y >= item_y - (player_s_y/2) && (item_x - player_x < player_s_x - 5 && player_x - item_x < GRID_SLOT_SIZE - 5))
                player.set_position({ player_x, item_y + player_s_y });
            else if (player_y >= item_y - player_s_y && (item_x - player_x < player_s_x - 5 && player_x - item_x < GRID_SLOT_SIZE - 5))
                player.set_position({ player_x, item_y - player_s_y });
        }
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

