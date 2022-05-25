#include "Game.h"
#include <fstream>
#include <string>
#include "../Exceptions/Item_exceptions.h"



void Game::play(int save_number, char type, bool new_game, sf::RenderWindow &window)
{
    if (!bomb_texture_.loadFromFile(BOMB_PATH))
    {
        throw (FliePathException());
    }
    play_story_(save_number, new_game, window, 1);
}

void Game::play_story_(int save_number, bool new_game, sf::RenderWindow &window, int number_of_players)
{
    sf::Texture player_texture;
    if (!player_texture.loadFromFile(PLAYER_PATH))
    {
        throw (FliePathException());
    }
    std::vector<std::shared_ptr<Player2> > players;
    for (int i = 0; i < number_of_players; i++)
    {
        players.push_back(std::make_shared<Player2>(Player2(TEXTURE_SCALE, player_texture)));
        players[i]->set_position({ 0, 0 });
    }


    const int MOVEMNT_SPEED = 5;
    int level_number = 1;
    window.setFramerateLimit(60);
    if (new_game)
    {
        std::vector<int> game_info = load_game(save_number, 'S');
        level_number = game_info[0];
        points_ = game_info[1];
    }

    StoryModeBoard story_b_(level_number, number_of_players);

    sf::Clock Clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || detect_player_door_colision(players, story_b_.get_door_global_bounds()))
            {
                save_game_(save_number, 'S', story_b_.level_number(), points_);
                window.close();
            }
        }
        int i = 0;
        for (std::shared_ptr< Player2> player : players)
        {
            move_player_(player, story_b_.items(), window, PLAYERS_KEYS[i]);
            if (sf::Keyboard::isKeyPressed(PLAYERS_KEYS[i][2]) && is_player_close_to_edge(player, window))
            {
                story_b_.move_items({ -MOVEMNT_SPEED, 0 });
                check_if_colides_right(player, story_b_.items(), window);
            }
            if (sf::Keyboard::isKeyPressed(PLAYERS_KEYS[i][3]) && player->getX() <= 50 && story_b_.item(0)->position().x < 1 * GRID_SLOT_SIZE)
            {
                story_b_.move_items({ MOVEMNT_SPEED, 0 });
                check_if_colides_left(player, story_b_.items(), window);
            }
            place_bombs_(player);
            i++;
        }

        window.clear(sf::Color(69, 159, 66));
        story_b_.draw_to(window);
        for (std::shared_ptr< Player2> player : players)
        {
            player->draw_to(window);
        }
        for (auto a : bombs_on_b_)
        {
            a->draw_to(window);
        }
        window.display();
        //std::cout << 1.f/Clock.getElapsedTime().asSeconds()<<"\n";
        //Clock.restart();
    }

    return;
}


void Game::move_player_(std::shared_ptr< Player2> player , std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window, std::vector<sf::Keyboard::Key> keys)
{
    float player_s_x = player->size().x;
    float player_s_y = player->size().y;
    float player_x = player->getX();
    float player_y = player->getY();
    float item_x = 0;
    float item_y = 0;
    const int MOVEMNT_SPEED = 5;
    if (sf::Keyboard::isKeyPressed(keys[0]))
    {
        player->move({ 0, -MOVEMNT_SPEED });
        check_if_colides_up(player, items_on_b, window);
    }
    else if (sf::Keyboard::isKeyPressed(keys[1]))
    {
        player->move({ 0, MOVEMNT_SPEED });
        check_if_colides_down(player, items_on_b, window);
    }
    if (sf::Keyboard::isKeyPressed(keys[2]) && not is_player_close_to_edge(player, window))
    {
        player->move({ MOVEMNT_SPEED, 0 });
        check_if_colides_right(player, items_on_b, window);
    }
    else if (sf::Keyboard::isKeyPressed(keys[3]) && (player_x >= 50 || not items_on_b[0]->position().x < 1 * GRID_SLOT_SIZE))
    {
        player->move({ - MOVEMNT_SPEED, 0 });
        check_if_colides_left(player, items_on_b, window);
    }
}

void Game::place_bombs_(std::shared_ptr< Player2> player)
{
    int player_p_x = player->getX();
    int player_p_y = player->getY();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        int bomb_pos_x = (player_p_x + BOMB_PLACEMENT_TOLERANCES) / GRID_SLOT_SIZE ;
        int bomb_pos_y = (player_p_y + BOMB_PLACEMENT_TOLERANCES) / GRID_SLOT_SIZE ;
        Bomb bomb({float(bomb_pos_x*GRID_SLOT_SIZE), float(bomb_pos_y*GRID_SLOT_SIZE)}, 5, MAX_EXPLOSION_DELAY, 1, TEXTURE_SCALE, bomb_texture_);
        bombs_on_b_.push_back(std::make_shared<Bomb>(bomb));
    }
}


void Game::check_if_colides_left(std::shared_ptr< Player2> player, std::vector<std::shared_ptr<Wall>> items_on_b, sf::RenderWindow& window)
{
    float player_s_x = player->size().x;
    float player_s_y = player->size().y;
    float player_x = player->getX();
    float player_y = player->getY();
    float item_x = 0;
    float item_y = 0;
    for (auto a : items_on_b)
    {
        if (a->is_coloding_player(player))
        {
            item_x = a->position().x;
            item_y = a->position().y;
            if (player_x <= item_x + GRID_SLOT_SIZE && player_x >= item_x - player_s_x / 2 && std::abs(item_y - player_y) < player_s_y - 5)
                player->set_position({ item_x + GRID_SLOT_SIZE, player_y });
        }
    }
    if (player_x <= 0)
    {
        player->set_position({ 0, player_y });
    }

}

void Game::check_if_colides_right(std::shared_ptr< Player2> player, std::vector<std::shared_ptr<Wall>> items_on_b, sf::RenderWindow& window)
{
    float player_s_x = player->size().x;
    float player_s_y = player->size().y;
    float player_x = player->getX();
    float player_y = player->getY();
    float item_x = 0;
    float item_y = 0;
    for (auto a : items_on_b)
    {
        if (a->is_coloding_player(player))
        {
            item_x = a->position().x;
            item_y = a->position().y;
            if (player_x >= item_x - player_s_x && player_x <= item_x - player_s_x / 2 && std::abs(item_y - player_y) < player_s_y - 5)
                player->set_position({ item_x - player_s_x, player_y });
        }
    }
    if (player_x >= window.getSize().x - GRID_SLOT_SIZE/2)
    {
        player->set_position({ float(window.getSize().x - GRID_SLOT_SIZE/2), player_y});
    }
}

void Game::check_if_colides_up(std::shared_ptr< Player2> player, std::vector<std::shared_ptr<Wall>> items_on_b, sf::RenderWindow& window)
{
    float player_s_x = player->size().x;
    float player_s_y = player->size().y;
    float player_x = player->getX();
    float player_y = player->getY();
    float item_x = 0;
    float item_y = 0;
    for (auto a : items_on_b)
    {
        if (a->is_coloding_player(player))
        {
            item_x = a->position().x;
            item_y = a->position().y;
            if (player_y <= item_y + player_s_y + (GRID_SLOT_SIZE*10/3) && player_y >= item_y - (player_s_y / 2) && (item_x - player_x < player_s_x - 5 && player_x - item_x < GRID_SLOT_SIZE - 5))
                player->set_position({ player_x, item_y + GRID_SLOT_SIZE });
        }
    }
    if (player_y <= 0)
    {
        player->set_position({ player_x, 0 });
    }
}

void Game::check_if_colides_down(std::shared_ptr< Player2> player, std::vector<std::shared_ptr<Wall>> items_on_b, sf::RenderWindow& window)
{
    float player_s_x = player->size().x;
    float player_s_y = player->size().y;
    float player_x = player->getX();
    float player_y = player->getY();
    float item_x = 0;
    float item_y = 0;
    for (auto a : items_on_b)
    {
        if (a->is_coloding_player(player))
        {
            item_x = a->position().x;
            item_y = a->position().y;
            if (player_y >= item_y - player_s_y && player_y <= item_y - (player_s_y / 2) && (item_x - player_x < player_s_x - 5 && player_x - item_x < GRID_SLOT_SIZE - 5))
                player->set_position({ player_x, item_y - player_s_y });
        }
    }
    if (player_y >= window.getSize().y - GRID_SLOT_SIZE)
    {
        player->set_position({ player_x, float(window.getSize().y - GRID_SLOT_SIZE) });
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

bool Game::is_player_close_to_edge(std::shared_ptr< Player2> player, sf::RenderWindow& window)
{
    return player->getX() >= 4 * window.getSize().x / 5;
}

std::vector<std::shared_ptr<Player2>> Game::create_players_(int player_number, sf::Texture &player_texture, bool versus_mode)
{
    std::vector<std::shared_ptr<Player2> > players;
    for (int i = 0; i < player_number; i++)
    {
        players.push_back(std::make_shared<Player2>(Player2(TEXTURE_SCALE, player_texture)));
        players[i]->set_position({ 0, 0 });
    }
}

bool Game::detect_player_door_colision(std::vector<std::shared_ptr<Player2> > players, const sf::FloatRect& door_bounds)
{
    for (std::shared_ptr< Player2> player : players)
    {
        if (door_bounds.intersects(player->get_global_bounds()))
            return true;
    }
    return false;
}
