#include "Game.h"
#include <fstream>
#include <string>
#include "../Exceptions/Item_exceptions.h"



void Game::play(int save_number, char type, bool new_game)
{
    if (!bomb_texture_.loadFromFile(BOMB_PATH))
    {
        throw (FliePathException());
    }
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

    sf::Texture player_texture;
    if (!player_texture.loadFromFile(PLAYER_PATH))
    {
        throw (FliePathException());
    }
    Player2 player({.14286, .14286}, player_texture);
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
        move_player_(player, story_b_.items(), window);
        place_bombs_(player);

        window.clear();
        story_b_.draw_to(window);
        player.draw_to(window);
        for (auto a : bombs_on_b_)
            a->draw_to(window);
        window.display();
        std::cout << 1.f/Clock.getElapsedTime().asSeconds()<<"\n";
        Clock.restart();
    }

    return;
}


void Game::move_player_(Player2& player , std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window)
{
    float player_s_x = player.size().x;
    float player_s_y = player.size().y;
    float player_x = player.getX();
    float player_y = player.getY();
    float item_x = 0;
    float item_y = 0;
    const int MOVEMNT_SPEED = 5;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player.move({ 0, -MOVEMNT_SPEED });
        for (auto a : items_on_b)
        {
            if (a->is_coloding_player(player))
            {
                item_x = a->position().x;
                item_y = a->position().y;
                if (player_y <= item_y + player_s_y+8 && player_y >= item_y - (player_s_y / 2) && (item_x - player_x < player_s_x - 5 && player_x - item_x < GRID_SLOT_SIZE - 5))
                    player.set_position({ player_x, item_y + GRID_SLOT_SIZE });
            }
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        player.move({ 0, MOVEMNT_SPEED });
        for (auto a : items_on_b)
        {
            if (a->is_coloding_player(player))
            {
                item_x = a->position().x;
                item_y = a->position().y;
                if (player_y >= item_y - player_s_y && (item_x - player_x < player_s_x - 5 && player_x - item_x < GRID_SLOT_SIZE - 5))
                    player.set_position({ player_x, item_y - player_s_y });
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.move({ MOVEMNT_SPEED, 0 });
        for (auto a : items_on_b)
        {
            if (a->is_coloding_player(player))
            {
                item_x = a->position().x;
                item_y = a->position().y;
                if (player_x >= item_x - player_s_x && player_x <= item_x - player_s_x / 2 && std::abs(item_y - player_y) < player_s_y - 5)
                    player.set_position({ item_x - player_s_x, player_y });
            }
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player.move({ - MOVEMNT_SPEED, 0 });
        for (auto a : items_on_b)
        {
            if (a->is_coloding_player(player))
            {
                item_x = a->position().x;
                item_y = a->position().y;
                if (player_x <= item_x + GRID_SLOT_SIZE && std::abs(item_y - player_y) < player_s_y - 5)
                    player.set_position({ item_x + GRID_SLOT_SIZE, player_y });
            }
        }
        //check_if_player_stops_(player, items_on_b, window);
    }
}

void Game::place_bombs_(Player2& player)
{
    int player_p_x = player.getX();
    int player_p_y = player.getY();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        int bomb_pos_x = player_p_x / GRID_SLOT_SIZE - player_p_x % GRID_SLOT_SIZE + 1;
        int bomb_pos_y = player_p_y / GRID_SLOT_SIZE - player_p_y % GRID_SLOT_SIZE + 1;
        Bomb bomb({float(bomb_pos_x*GRID_SLOT_SIZE), float(bomb_pos_y*GRID_SLOT_SIZE)}, 5, MAX_EXPLOSION_DELAY, 1, {0.14286, 0.14286 }, bomb_texture_);
        bombs_on_b_.push_back(std::make_shared<Bomb>(bomb));
        std::cout << "a";
    }
}

void Game::check_if_player_stops_(Player2& player, std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow &window)
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
                player.set_position({ item_x - player_s_x-1, player_y });
            else if (player_x <= item_x + GRID_SLOT_SIZE && std::abs(item_y - player_y) < player_s_y - 5) 
                player.set_position({ item_x + GRID_SLOT_SIZE+1, player_y });
            if (player_y <= item_y + player_s_y + 2  && player_y >= item_y - (player_s_y/2) && (item_x - player_x < player_s_x - 5 && player_x - item_x < GRID_SLOT_SIZE - 5))
                player.set_position({ player_x, item_y + GRID_SLOT_SIZE + 1 });
            else if (player_y >= item_y - player_s_y && (item_x - player_x < player_s_x - 5 && player_x - item_x < GRID_SLOT_SIZE - 5))
                player.set_position({ player_x, item_y - player_s_y  -1});
        }
    }
    //sf::Vector2u win_size = window.getSize();
    //if (player_x <= 0) player.set_position({ 0, player_y });
    //else if (player_x >= win_size.x) player.set_position({ float(win_size.x), player_y + player_s_y });
    //if (player_y <= 0) player.set_position({ player_x, 0 });
    //else if (player_y >= win_size.y) player.set_position({ player_x + player_s_x, float(win_size.y)});
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

