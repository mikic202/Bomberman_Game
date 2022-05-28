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
    //play_versus_(window);
    play_story_(save_number, new_game, window, 1);
}

void Game::play_story_(int save_number, bool new_game, sf::RenderWindow &window, int number_of_players)
{
    int level_points;
    int pixeles_moved;

    create_players_(number_of_players);


    const int MOVEMNT_SPEED = 5;
    int level_number = 1;
    window.setFramerateLimit(60);
    if (new_game)
    {
        std::vector<int> game_info = load_game(save_number, 'S');
        level_number = game_info[0];
        points_ = game_info[1];
    }
    sf::Texture explosion_texture;
    if (!explosion_texture.loadFromFile(EXPLOSION_PATH))
    {
        throw (FliePathException());
    }
    StoryModeBoard story_b_(level_number, number_of_players);

    sf::Clock Clock;
    while (window.isOpen())
    {
        level_points = 0;
        pixeles_moved = 0;
        for (auto player : players_)
        {
            player->set_position({0, 0});
        }
        while (not detect_player_door_colision(story_b_.get_door_global_bounds()))
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
            int i = 0;
            for (auto player : players_)
            {
                move_player_(player, story_b_.items(), window, PLAYERS_KEYS[i], pixeles_moved);
                if (sf::Keyboard::isKeyPressed(PLAYERS_KEYS[i][2]) && is_player_close_to_edge(player, window)&& pixeles_moved != 30*GRID_SLOT_SIZE - window.getSize().x)
                {
                    story_b_.move_items({ -MOVEMNT_SPEED, 0 });
                    for (auto bomb : bombs_on_b_)
                    {
                        bomb->move({ -MOVEMNT_SPEED, 0 });
                    }
                    for (auto explosion : explosions_)
                    {
                        explosion->move({ -MOVEMNT_SPEED, 0 });
                    }
                    pixeles_moved += MOVEMNT_SPEED;
                    check_if_colides_right(player, story_b_.items(), window);
                }
                if (sf::Keyboard::isKeyPressed(PLAYERS_KEYS[i][3]) && player->get_position().x <= 50 && story_b_.item(0)->position().x < 1 * GRID_SLOT_SIZE)
                {
                    story_b_.move_items({ MOVEMNT_SPEED, 0 });
                    for (auto bomb : bombs_on_b_)
                    {
                        bomb->move({ MOVEMNT_SPEED, 0 });
                    }
                    for (auto explosion : explosions_)
                    {
                        explosion->move({ MOVEMNT_SPEED, 0 });
                    }
                    pixeles_moved -= MOVEMNT_SPEED;
                    check_if_colides_left(player, story_b_.items(), window);
                }
                place_bombs_(player, PLAYERS_KEYS[i][4]);
                i++;
            }
            bobm_explosion_(story_b_.items());
            window.clear(sf::Color(69, 159, 66));
            story_b_.draw_to(window);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                explosions_.clear();
                explosions_on_board_ = 0;
            }
            for (auto player : players_)
            {
                player->draw_to(window);
            }
            for (auto a : bombs_on_b_)
            {
                a->draw_to(window);
            }
            for (auto explo : explosions_)
            {
                explo->draw_to(window);
            }
            window.display();
            //std::cout << 1.f/Clock.getElapsedTime().asSeconds()<<"\n";
            //Clock.restart();
        }
        story_b_.reset_board(++level_number);
        points_ += 500+level_points;
    }

    return;
}


void Game::play_versus_(sf::RenderWindow& window)
{
    create_players_(2, true, 11);

    const int MOVEMNT_SPEED = 5;
    int level_number = 1;
    window.setFramerateLimit(60);

    VersusModeBoard versus_board_(11);

    sf::Clock Clock;
    while (window.isOpen())
    {
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }
            int i = 0;
            for (auto player : players_)
            {
                move_player_(player, versus_board_.items(), window, PLAYERS_KEYS[i], 0, true);
                i++;
            }

            window.clear(sf::Color(69, 159, 66));
            versus_board_.draw_to(window);
            for (auto player : players_)
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
    }

    return;
}

void Game::move_player_(std::shared_ptr< Player> player , std::vector<std::shared_ptr<Wall> > items_on_b, sf::RenderWindow& window, std::vector<sf::Keyboard::Key> keys, int pixels_moved, bool versus)
{
    float player_x = player->get_position().x;
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
    if (sf::Keyboard::isKeyPressed(keys[2]) && (not is_player_close_to_edge(player, window) || pixels_moved >= 30 * GRID_SLOT_SIZE - window.getSize().x||versus))
    {
        player->move({ MOVEMNT_SPEED, 0 });
        check_if_colides_right(player, items_on_b, window);
    }
    else if (sf::Keyboard::isKeyPressed(keys[3]) && (player_x >= 50 || not items_on_b[0]->position().x < 1 * GRID_SLOT_SIZE||versus))
    {
        player->move({ - MOVEMNT_SPEED, 0 });
        check_if_colides_left(player, items_on_b, window);
    }
}

void Game::place_bombs_(std::shared_ptr< Player> player, sf::Keyboard::Key bomb_placing)
{
    int player_p_x = player->get_position().x;
    int player_p_y = player->get_position().y;
    if (sf::Keyboard::isKeyPressed(bomb_placing))
    {
        if (not player->on_bomb(bombs_on_b_))
        {
            int bomb_pos_x = (player_p_x + BOMB_PLACEMENT_TOLERANCES) / GRID_SLOT_SIZE;
            int bomb_pos_y = (player_p_y + BOMB_PLACEMENT_TOLERANCES) / GRID_SLOT_SIZE;
            Bomb bomb({ float(bomb_pos_x * GRID_SLOT_SIZE), float(bomb_pos_y * GRID_SLOT_SIZE) }, 5, MAX_EXPLOSION_DELAY, 1, TEXTURE_SCALE, bomb_texture_);
            bombs_on_b_.push_back(std::make_shared<Bomb>(bomb));
        }
    }
}


void Game::check_if_colides_left(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall>> items_on_b, sf::RenderWindow& window)
{
    float player_s_x = PLAYER_TEXTURE_SIZE[0];
    float player_s_y = PLAYER_TEXTURE_SIZE[1];
    float player_x = player->get_position().x;
    float player_y = player->get_position().y;
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

void Game::check_if_colides_right(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall>> items_on_b, sf::RenderWindow& window)
{
    float player_s_x = PLAYER_TEXTURE_SIZE[0];
    float player_s_y = PLAYER_TEXTURE_SIZE[1];
    float player_x = player->get_position().x;
    float player_y = player->get_position().y;
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

void Game::check_if_colides_up(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall>> items_on_b, sf::RenderWindow& window)
{
    float player_s_x = PLAYER_TEXTURE_SIZE[0];
    float player_s_y = PLAYER_TEXTURE_SIZE[1];
    float player_x = player->get_position().x;
    float player_y = player->get_position().y;
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

void Game::check_if_colides_down(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall>> items_on_b, sf::RenderWindow& window)
{
    float player_s_x = PLAYER_TEXTURE_SIZE[0];
    float player_s_y = PLAYER_TEXTURE_SIZE[1];
    float player_x = player->get_position().x;
    float player_y = player->get_position().y;
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

bool Game::is_player_close_to_edge(std::shared_ptr< Player> player, sf::RenderWindow& window)
{
    return player->get_position().x >= 4 * window.getSize().x / 5;
}

void Game::create_players_(int player_number, bool versus_mode, int game_board_size)
{
    sf::Vector2f start_position = { 0, 0 };
    if (!player1_texture_.loadFromFile(PLAYER_PATH))
    {
        throw (FliePathException());
    }
    players_.push_back(std::make_shared<Player>(Player(start_position, player1_texture_, TEXTURE_SCALE, 1)));
    if (player_number == 2 && not versus_mode)
    {
        if (!player2_texture_.loadFromFile(PLAYER_PATH))
        {
            throw (FliePathException());
        }
        players_.push_back(std::make_shared<Player>(Player(start_position, player2_texture_, TEXTURE_SCALE, 1)));
    }
    else if (player_number == 2 && versus_mode)
    {
        if (!player2_texture_.loadFromFile(PLAYER_PATH))
        {
            throw (FliePathException());
        }
        players_.push_back(std::make_shared<Player>(Player({ float((game_board_size-1) * GRID_SLOT_SIZE), float((game_board_size - 1) * GRID_SLOT_SIZE)}, player2_texture_, TEXTURE_SCALE, 1)));
    }
}

bool Game::detect_player_door_colision(const sf::FloatRect& door_bounds)
{
    for (auto player : players_)
    {
        if (door_bounds.intersects(player->get_global_bounds()))
            return true;
    }
    return false;
}

void Game::bobm_explosion_(std::vector<std::shared_ptr<Wall>> items_on_b)
{
    for (int i = 0; i < bombs_on_b_.size();i++)
    {
        if (bombs_on_b_[i]->did_blow())
        {
            place_explosion_(items_on_b, bombs_on_b_[i]);
            bombs_on_b_.erase(bombs_on_b_.begin() + i);
            i--;
        }
    }
}

void Game::place_explosion_(std::vector<std::shared_ptr<Wall>> items_on_b, std::shared_ptr<Bomb> bomb)
{
    int bomb_pos_x = bomb->position().x;
    int bomb_pos_y = bomb->position().y;
    if (!explosion_texture_.loadFromFile(EXPLOSION_PATH))
    {
        throw (FliePathException());
    }
    explosions_.push_back(std::make_shared<Explosion>(Explosion({ float(bomb_pos_x),float(bomb_pos_y) }, TEXTURE_SCALE, explosion_texture_)));
    for (int i = 1; i <= bomb->radius(); i++)
    {
        explosions_.push_back(std::make_shared<Explosion>(Explosion({ float(bomb_pos_x - GRID_SLOT_SIZE * i),float( bomb_pos_y+3) }, { float(TEXTURE_SCALE.x), float(TEXTURE_SCALE.y - 0.02) }, explosion_texture_)));

        explosions_.push_back(std::make_shared<Explosion>(Explosion({ float(bomb_pos_x + GRID_SLOT_SIZE * i),float(bomb_pos_y+3) }, { float(TEXTURE_SCALE.x), float(TEXTURE_SCALE.y - 0.02) }, explosion_texture_)));

        explosions_.push_back(std::make_shared<Explosion>(Explosion({ float(bomb_pos_x+3),float(bomb_pos_y - GRID_SLOT_SIZE * i) }, { float(TEXTURE_SCALE.x - 0.02), float(TEXTURE_SCALE.y) }, explosion_texture_)));

        explosions_.push_back(std::make_shared<Explosion>(Explosion({ float(bomb_pos_x+3),float(bomb_pos_y + GRID_SLOT_SIZE * i) }, { float(TEXTURE_SCALE.x - 0.02), float(TEXTURE_SCALE.y) }, explosion_texture_)));
    }
    check_where_explosion_stops(items_on_b, bomb);
}

void Game::check_where_explosion_stops(std::vector<std::shared_ptr<Wall>> items_on_b, std::shared_ptr<Bomb> bomb)
{
    explosions_on_board_++;
    int bomb_pos_x = bomb->position().x;
    int bomb_pos_y = bomb->position().y;
    std::vector<int> explosionc_to_destroy;
    std::vector<bool> eplosion_not_stopped = { true, true, true, true };
    for (int i = 0; i < bomb->radius(); i++)
    {
        if (eplosion_not_stopped[0])
        {
            for (auto item : items_on_b)
            {
                if ((item->position().x > bomb_pos_x - GRID_SLOT_SIZE * bomb->radius() || item->position().x < bomb_pos_x + GRID_SLOT_SIZE * bomb->radius()) &&
                (item->position().y > bomb_pos_y - GRID_SLOT_SIZE * bomb->radius() || item->position().y < bomb_pos_y + GRID_SLOT_SIZE * bomb->radius()))
                {
                    if (explosions_[explosions_on_board_ - 1 +4*i+1]->get_global_bounds().intersects(item->get_global_bounds()))
                    {
                        eplosion_not_stopped[0] = false;
                        explosionc_to_destroy.push_back(4*i+1);
                    }
                }
            }
        }
        else
        {
            explosionc_to_destroy.push_back(4*i+1);
        }

        if (eplosion_not_stopped[1])
        {
            for (auto item : items_on_b)
            {
                if ((item->position().x > bomb_pos_x - GRID_SLOT_SIZE * bomb->radius() || item->position().x < bomb_pos_x + GRID_SLOT_SIZE * bomb->radius()) &&
                    item->position().y > bomb_pos_y - GRID_SLOT_SIZE * bomb->radius() || item->position().y < bomb_pos_y + GRID_SLOT_SIZE * bomb->radius())
                {
                    if (explosions_[explosions_on_board_ - 1 + 4 * i + 2]->get_global_bounds().intersects(item->get_global_bounds()))
                    {
                        eplosion_not_stopped[1] = false;
                        explosionc_to_destroy.push_back(4 * i + 2);
                    }
                }
            }
        }
        else
        {
            explosionc_to_destroy.push_back(4 * i + 2);
        }

        if (eplosion_not_stopped[2])
        {
            for (auto item : items_on_b)
            {
                if ((item->position().x > bomb_pos_x - GRID_SLOT_SIZE * bomb->radius() || item->position().x < bomb_pos_x + GRID_SLOT_SIZE * bomb->radius()) &&
                    item->position().y > bomb_pos_y - GRID_SLOT_SIZE * bomb->radius() || item->position().y < bomb_pos_y + GRID_SLOT_SIZE * bomb->radius())
                {
                    if (explosions_[explosions_on_board_ - 1 + 4 * i + 3]->get_global_bounds().intersects(item->get_global_bounds()))
                    {
                        eplosion_not_stopped[2] = false;
                        explosionc_to_destroy.push_back(4 * i + 3);
                    }
                }
            }
        }
        else
        {
            explosionc_to_destroy.push_back(4 * i + 3);
        }

        if (eplosion_not_stopped[3])
        {
            for (auto item : items_on_b)
            {
                if ((item->position().x > bomb_pos_x - GRID_SLOT_SIZE * bomb->radius() || item->position().x < bomb_pos_x + GRID_SLOT_SIZE * bomb->radius()) &&
                    item->position().y > bomb_pos_y - GRID_SLOT_SIZE * bomb->radius() || item->position().y < bomb_pos_y + GRID_SLOT_SIZE * bomb->radius())
                {
                    if (explosions_[explosions_on_board_ -1 + 4 * i + 4]->get_global_bounds().intersects(item->get_global_bounds()))
                    {
                        eplosion_not_stopped[3] = false;
                        explosionc_to_destroy.push_back(4*i+4);
                    }
                }
            }
        }
        else
        {
            explosionc_to_destroy.push_back(4*i + 4);
        }
    }
    for (int j = explosionc_to_destroy.size() - 1; j >= 0; j--)
    {
        explosions_.erase(explosions_.begin() + explosions_on_board_ - 1+explosionc_to_destroy[j]);
    }
    explosions_on_board_ = explosions_.size();

}
