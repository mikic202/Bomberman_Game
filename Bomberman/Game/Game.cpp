//Miko³aj Chomanski

#include "Game.h"
#include <fstream>
#include <thread>
#include <string>
#include "../Exceptions/Item_exceptions.h"
#include "../Menu/PauseMenu.h"


const int POINTS_PER_BOX = 20;
const int POINTS_PER_ENEMY = 40;



void Game::play(int save_number, char type, bool new_game, sf::RenderWindow &window)
{
    if (!bomb_texture_.loadFromFile(BOMB_PATH))
    {
        throw (FliePathException());
    }
    if (!door_texture_.loadFromFile(DOOR_PATH))
    {
        throw (FliePathException());
    }
    if (!box_texture_.loadFromFile(BOX_PATH))
    {
        throw (FliePathException());
    }
    if (!wall_texture_.loadFromFile(WALL_PATH))
    {
        throw (FliePathException());
    }
    if (!explosion_texture_.loadFromFile(EXPLOSION_PATH))
    {
        throw (FliePathException());
    }
    if (!enemy_texture_.loadFromFile(ENEMY_PATH))
    {
        throw (FliePathException());
    }
    window.setFramerateLimit(60);
    if (type == 'S')
    {
        play_story_(save_number, new_game, window, 1); 
    }
    else if (type == 'V')
    {
        play_versus_(window);
    }
    else if (type == 'C')
    {
        play_coop_(save_number+3, new_game, window);
    }
    return;
}

void Game::play_story_(int save_number, bool new_game, sf::RenderWindow &window, int number_of_players)
{
    bool need_to_run = true;
    players_.clear();

    int level_points;
    int pixeles_moved;

    create_players_(number_of_players);

    const int MOVEMNT_SPEED = 5;
    int level_number = 1;
    window.setFramerateLimit(60);
    points_ = 0;

    if (not new_game)
    {
        std::vector<int> game_info = load_game_(save_number, 'S');
        level_number = game_info[0];
        points_ = game_info[1];
    }
    game_board_ = std::make_shared<StoryModeBoard>(StoryModeBoard(level_number, number_of_players, wall_texture_, box_texture_, door_texture_));
    int items_number_before_loop = 0;
    int enemies_number_before_loop = 0;
    pixels_moved_ = 0;
    PauseMenu p_menu('S', window, 1);

    while (window.isOpen() && need_to_run)
    {
        level_points = 0;
        for (auto player : players_)
        {
            player->set_position({0, 0});
        }
        if (check_if_players_are_dead_())
        {
            for (auto player : players_)
            {
                player->set_hp(3);
            }
        }
        generate_enemies_();
        items_number_before_loop = game_board_->items().size();
        enemies_number_before_loop = enemies_.size();
        while (detect_player_door_colision_(game_board_->get_door_global_bounds()) && need_to_run && not check_if_players_are_dead_())
        {

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    save_game_(save_number, 'S', game_board_->level_number(), points_);
                    window.close();
                    exit(1);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                p_menu.run();
                need_to_run = p_menu.get_can_game_continue();
                p_menu.set_is_menu_open(true);
            }

            int i = 0;
            move_players_(window);
            std::thread move_enem(&Game::move_enemies_, this);
            for (auto player : players_)
            {
                place_bombs_(player, PLAYERS_KEYS[i][4], pixels_moved_);
                i++;
            }

            bomb_explosion_(game_board_->items());
            if(kill_players_(pixels_moved_))
                pixels_moved_ = 0;

            window.clear(sf::Color(69, 159, 66));
            draw_game_(window);
            draw_score_(window, (points_ + level_points));
            window.display();
            level_points = POINTS_PER_BOX*(items_number_before_loop - game_board_->items().size()) + POINTS_PER_ENEMY*(enemies_number_before_loop-enemies_.size());
            move_enem.join();
        }
        game_board_->reset_board(++level_number, wall_texture_, box_texture_, door_texture_);
        pixels_moved_ = 0;
        if (need_to_run && not check_if_players_are_dead_())
            display_level_statistic_(level_points, items_number_before_loop - game_board_->items().size(), enemies_number_before_loop - enemies_.size(), window);
        enemies_.clear();
        if (check_if_players_are_dead_())
        {
            game_board_->reset_board(level_number, wall_texture_, box_texture_, door_texture_);
            for (auto player : players_)
            {
                player->set_hp(3);
                continue;
            }
        }
        points_ += 500+level_points;
    }
    save_game_(save_number, 'S', game_board_->level_number(), points_);
    return;
}

void Game::play_versus_(sf::RenderWindow& window)
{
    bool need_to_run = true;
    const int MOVEMNT_SPEED = 5;
    sf::Texture explosion_texture;
    game_board_ = std::make_shared<VersusModeBoard>(VersusModeBoard(NUMBER_OF_WALLS_Y, wall_texture_, box_texture_));
    PauseMenu p_menu('S', window, 1);
    while (window.isOpen() && need_to_run)
    {
        create_players_(2, true, NUMBER_OF_WALLS_Y);
        while (players_[0]->get_hp() == players_[1]->get_hp() && need_to_run)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                    exit(1);
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                p_menu.run();
                need_to_run = p_menu.get_can_game_continue();
                p_menu.set_is_menu_open(true);
            }

            int i = 0;
            move_players_(window, true);
            for (auto player : players_)
            {
                place_bombs_(player, PLAYERS_KEYS[i][4], 0);
                i++;
            }
            bomb_explosion_(game_board_->items());
            kill_players_(0, true);

            window.clear(sf::Color(69, 159, 66));
            draw_game_(window);
            window.display();

        }
        if(need_to_run)
            draw_result_(window);

        explosions_on_board_ = 0;
        game_board_->reset_board(NUMBER_OF_WALLS_Y,wall_texture_, box_texture_, door_texture_);
        bombs_on_b_.clear();
        players_.clear();
    }

    return;
}

void Game::play_coop_(int save_number, bool new_game, sf::RenderWindow& window)
{
    play_story_(save_number, new_game, window, 2);
}

void Game::move_players_(sf::RenderWindow& window, bool versus)
{
    /**
    * this method is responsible for player movement
    * It takes in two parameters:
    * *Reference of the render window
    * *Bool information wheather game mode is versus
    * In the front we can se that players texture is changed to static
    * Than six if statements determine which side player is moving or maby board is moving
    * each if check if the player is cooliding with anything and based on that it determines whether
    * to move or stop player or to move whole board insted
    * 
    * All of the colisions checkin methods are similar
    * first they check if player intersects with object
    * than it check whether object solides from correct side
    * if yes than players position is set to noe in right in front of that object
    */
    for (int i = 0; i < players_.size(); i++)
    {
        std::shared_ptr<Player> player = players_[i];
        std::vector<sf::Keyboard::Key> keys = PLAYERS_KEYS[i];

        if (not (sf::Keyboard::isKeyPressed(keys[0]) || sf::Keyboard::isKeyPressed(keys[1]) || sf::Keyboard::isKeyPressed(keys[2]) || sf::Keyboard::isKeyPressed(keys[3])) && not player->can_textured_be_placed(50) && is_player_stationary_[i] != 1)
        {
            if (i == 0 && !player1_texture_.loadFromFile(PLAYER_PATH))
            {
                throw (FliePathException());
            }
            if (i == 1 && !player2_texture_.loadFromFile(PLAYER_PATH))
            {
                throw (FliePathException());
            }
            is_player_stationary_[i] = 1;
        }


        float player_x = player->get_position().x;
        const int MOVEMNT_SPEED = 5;
        if (sf::Keyboard::isKeyPressed(keys[0]))
        {
            player->move({ 0, -MOVEMNT_SPEED });
            check_if_colides_up_(player, game_board_->items(), window);
            display_player_move_forward_(player);
            is_player_stationary_[i] = 0;
        }
        else if (sf::Keyboard::isKeyPressed(keys[1]))
        {
            player->move({ 0, MOVEMNT_SPEED });
            check_if_colides_down_(player, game_board_->items(), window);
            display_player_move_backward_(player);
            is_player_stationary_[i] = 0;
        }
        if (sf::Keyboard::isKeyPressed(keys[2]) && (not is_player_close_to_edge_(player, window) || pixels_moved_ >= 30 * GRID_SLOT_SIZE - window.getSize().x || versus))
        {
            player->move({ MOVEMNT_SPEED, 0 });
            check_if_colides_right_(player, game_board_->items(), window);
            display_player_move_sideways_(player, 1);
            is_player_stationary_[i] = 0;
        }
        else if (sf::Keyboard::isKeyPressed(keys[3]) && (player_x >= 50 || not game_board_->items()[0]->position().x < 1 * GRID_SLOT_SIZE || versus))
        {
            player->move({ -MOVEMNT_SPEED, 0 });
            check_if_colides_left_(player, game_board_->items(), window);
            display_player_move_sideways_(player, -1);
            is_player_stationary_[i] = 0;
        }
        if (sf::Keyboard::isKeyPressed(PLAYERS_KEYS[i][2]) && can_gameboard_be_shifter_(true, window) && not versus)
        {
            shift_game_board_(-MOVEMNT_SPEED, i);
            check_if_colides_right_(player, game_board_->items(), window);
            display_player_move_sideways_(player, 1);
            is_player_stationary_[i] = 0;
        }
        if (sf::Keyboard::isKeyPressed(PLAYERS_KEYS[i][3]) && can_gameboard_be_shifter_(false, window) && not versus)
        {
            shift_game_board_(MOVEMNT_SPEED, i);
            display_player_move_sideways_(player, -1);
            check_if_colides_left_(player, game_board_->items(), window);
            is_player_stationary_[i] = 0;
        }
    }
}

void Game::shift_game_board_(float distance, int player_num)
{
    game_board_->move_items({ distance, 0 });
    for (auto bomb : bombs_on_b_)
    {
        bomb->move({ distance, 0 });
    }
    for (auto explosion : explosions_)
    {
        explosion->move({ distance, 0 });
    }
    pixels_moved_ -= distance;
    for (int i = 0; i < players_.size(); i++)
    {
        if (i != player_num)
        {
            players_[i]->move({ distance, 0 });
        }
    }
    for (auto enemy : enemies_)
    {
        enemy->set_position({ enemy->get_position().x + distance, enemy->get_position().y });
    }
}

bool Game::can_gameboard_be_shifter_( bool right, sf::RenderWindow &window)
{
    bool to_return = false;
    for (auto player : players_)
    {
        if (right && check_if_colides_right_(player, game_board_->items(), window) &&  not is_player_close_to_edge_(player, window) && not (pixels_moved_ != 30 * GRID_SLOT_SIZE - window.getSize().x))
        {
            return false;
        }
        else if (not right && check_if_colides_left_(player, game_board_->items(), window) && not (player->get_position().x <= 50) && not(game_board_->item(0)->position().x < 1 * GRID_SLOT_SIZE))
        {
            return false;
        }
        if (right && not check_if_colides_right_(player, game_board_->items(), window) && is_player_close_to_edge_(player, window) && (pixels_moved_ != 30 * GRID_SLOT_SIZE - window.getSize().x))
        {
            to_return = true;
        }
        else if (not right && not check_if_colides_left_(player, game_board_->items(), window) && (player->get_position().x <= 50) && (game_board_->item(0)->position().x < 1 * GRID_SLOT_SIZE))
        {
            to_return = true;
        }
        for (auto player2 : players_)
        {
            if (player2->get_position().x <= 50 && right)
            {
                return false;
            }
            else if (is_player_close_to_edge_(player2, window) && not right)
            {
                return false;
            }
        }
    }
    return to_return;
}

void Game::place_bombs_(std::shared_ptr< Player> player, sf::Keyboard::Key bomb_placing, int pixels_moved)
{
    int explosion_delay = 2;
    int player_p_x = player->get_position().x;
    int player_p_y = player->get_position().y;
    int multiplier = 0;
    if (pixels_moved > 0 && pixels_moved%GRID_SLOT_SIZE > GRID_SLOT_SIZE/5)
    {
        multiplier = 1;
    }
    if (sf::Keyboard::isKeyPressed(bomb_placing))
    {
        if (not player->on_bomb(bombs_on_b_))
        {
            int bomb_pos_x = (player_p_x + BOMB_PLACEMENT_TOLERANCES) / GRID_SLOT_SIZE;
            int bomb_pos_y = (player_p_y + BOMB_PLACEMENT_TOLERANCES) / GRID_SLOT_SIZE;
            Bomb bomb({ float(bomb_pos_x * GRID_SLOT_SIZE - pixels_moved % GRID_SLOT_SIZE+multiplier*GRID_SLOT_SIZE), float(bomb_pos_y * GRID_SLOT_SIZE) }, 4, explosion_delay, 1, TEXTURE_SCALE, bomb_texture_);
            bombs_on_b_.push_back(std::make_shared<Bomb>(bomb));
        }
    }
}

bool Game::check_if_colides_left_(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall>> items_on_b, sf::RenderWindow& window)
{
    float player_s_x = PLAYER_TEXTURE_SIZE[0];
    float player_s_y = PLAYER_TEXTURE_SIZE[1];
    float player_x = player->get_position().x;
    float player_y = player->get_position().y;
    float item_x = 0;
    float item_y = 0;
    for (auto a : items_on_b)
    {
        if (a->is_coloding_player(player) && not std::dynamic_pointer_cast<Door>(a))
        {
            item_x = a->position().x;
            item_y = a->position().y;
            if (player_x <= item_x + GRID_SLOT_SIZE && player_x >= item_x - player_s_x / 2 && std::abs(item_y - player_y) < player_s_y + 15)
            {
                player->set_position({ item_x + GRID_SLOT_SIZE, player_y });
                return true;
            }
        }
    }
    if (player_x < 0)
    {
        player->set_position({ 0, player_y });
        return true;
    }
    return false;
}

bool Game::check_if_colides_right_(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall>> items_on_b, sf::RenderWindow& window)
{
    float player_s_x = PLAYER_TEXTURE_SIZE[0];
    float player_s_y = PLAYER_TEXTURE_SIZE[1];
    float player_x = player->get_position().x;
    float player_y = player->get_position().y;
    float item_x = 0;
    float item_y = 0;
    for (auto a : items_on_b)
    {
        if (a->is_coloding_player(player) && not std::dynamic_pointer_cast<Door>(a))
        {
            item_x = a->position().x;
            item_y = a->position().y;
            if (player_x >= item_x - player_s_x && player_x <= item_x - player_s_x / 2 && std::abs(item_y - player_y) < player_s_y + 15)
            {
                player->set_position({ item_x - player_s_x, player_y });
                return true;
            }
        }
    }
    if (player_x >= window.getSize().x - GRID_SLOT_SIZE/2)
    {
        player->set_position({ float(window.getSize().x - GRID_SLOT_SIZE/2), player_y});
        return true;
    }
    return false;
}

void Game::check_if_colides_up_(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall>> items_on_b, sf::RenderWindow& window)
{
    float player_s_x = PLAYER_TEXTURE_SIZE[0];
    float player_s_y = PLAYER_TEXTURE_SIZE[1];
    float player_x = player->get_position().x;
    float player_y = player->get_position().y;
    float item_x = 0;
    float item_y = 0;
    for (auto a : items_on_b)
    {
        if (a->is_coloding_player(player) && not std::dynamic_pointer_cast<Door>(a))
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

void Game::check_if_colides_down_(std::shared_ptr< Player> player, std::vector<std::shared_ptr<Wall>> items_on_b, sf::RenderWindow& window)
{
    float player_s_x = PLAYER_TEXTURE_SIZE[0];
    float player_s_y = PLAYER_TEXTURE_SIZE[1];
    float player_x = player->get_position().x;
    float player_y = player->get_position().y;
    float item_x = 0;
    float item_y = 0;
    for (auto a : items_on_b)
    {
        if (a->is_coloding_player(player) && not std::dynamic_pointer_cast<Door>(a))
        {
            item_x = a->position().x;
            item_y = a->position().y;
            if (player_y >= item_y - player_s_y && player_y <= item_y - (player_s_y / 2) && (item_x - player_x < player_s_x - 5 && player_x - item_x < GRID_SLOT_SIZE - 5))
                player->set_position({ player_x, item_y - player_s_y });
        }
    }
    if (player_y >= window.getSize().y - GRID_SLOT_SIZE + 20)
    {
        player->set_position({ player_x, float(window.getSize().y - GRID_SLOT_SIZE+20) });
    }
}

void Game::save_game_(int save_number, char type, int leve_number, int points)
{
    std::ofstream save_file;
    if (save_number <= 3)
    {
        save_file.open(STORY_SAVES.at(save_number));
    }
    else if (save_number > 3)
    {
        save_file.open(CO_OP_SAVES.at(save_number - 3));
    }
    save_file << leve_number;
    save_file << "\n";
    save_file << points;
    save_file.close();
}

std::vector<int> Game::load_game_(int save_number, char type)
{
    std::string line;
    int level_number;
    std::ifstream save_file;
    if (save_number <= 3)
    {
        save_file.open(STORY_SAVES.at(save_number));
    }
    else if (save_number > 3)
    {
        save_file.open(CO_OP_SAVES.at(save_number-3));
    }
    std::getline(save_file, line);
    level_number = std::stoi(line);
    std::getline(save_file, line);
    save_file.close();
    return std::vector<int> {level_number, std::stoi(line)};
}

bool Game::is_player_close_to_edge_(std::shared_ptr< Player> player, sf::RenderWindow& window)
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
        player2_texture_.setSrgb(true);
    }
    else if (player_number == 2 && versus_mode)
    {
        if (!player2_texture_.loadFromFile(PLAYER_PATH))
        {
            throw (FliePathException());
        }
        players_.push_back(std::make_shared<Player>(Player({ float((game_board_size-1) * GRID_SLOT_SIZE), float((game_board_size - 1) * GRID_SLOT_SIZE)}, player2_texture_, TEXTURE_SCALE, 1)));
        player2_texture_.setSrgb(true);
    }
}

bool Game::detect_player_door_colision_(const sf::FloatRect& door_bounds)
{
    for (auto player : players_)
    {
        if (not door_bounds.intersects(player->get_global_bounds()))
            return true;
    }
    return false;
}

void Game::bomb_explosion_(std::vector<std::shared_ptr<Wall>> items_on_b)
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
    /**
    * This method is responsible for placing explosions on the board
    * 
    * It takes vector of walls and boxes, and vector of bombs
    * 
    * It places them in parts of four one for each arm of the cross pattern
    * then it uses check_where_explosion_stops_ to determin which explosions need to be deleted
    */
    int bomb_pos_x = bomb->position().x;
    int bomb_pos_y = bomb->position().y;
    explosions_.push_back(std::make_shared<Explosion>(Explosion({ float(bomb_pos_x),float(bomb_pos_y) }, TEXTURE_SCALE, explosion_texture_)));
    for (int i = 1; i <= bomb->radius(); i++)
    {
        explosions_.push_back(std::make_shared<Explosion>(Explosion({ float(bomb_pos_x - GRID_SLOT_SIZE * i),float( bomb_pos_y+3) }, { float(TEXTURE_SCALE.x), float(TEXTURE_SCALE.y - 0.02) }, explosion_texture_)));

        explosions_.push_back(std::make_shared<Explosion>(Explosion({ float(bomb_pos_x + GRID_SLOT_SIZE * i),float(bomb_pos_y+3) }, { float(TEXTURE_SCALE.x), float(TEXTURE_SCALE.y - 0.02) }, explosion_texture_)));

        explosions_.push_back(std::make_shared<Explosion>(Explosion({ float(bomb_pos_x+3),float(bomb_pos_y - GRID_SLOT_SIZE * i) }, { float(TEXTURE_SCALE.x - 0.02), float(TEXTURE_SCALE.y) }, explosion_texture_)));

        explosions_.push_back(std::make_shared<Explosion>(Explosion({ float(bomb_pos_x+3),float(bomb_pos_y + GRID_SLOT_SIZE * i) }, { float(TEXTURE_SCALE.x - 0.02), float(TEXTURE_SCALE.y) }, explosion_texture_)));
    }
    check_where_explosion_stops_(items_on_b, bomb);
}

void Game::check_where_explosion_stops_(std::vector<std::shared_ptr<Wall> > items_on_b, std::shared_ptr<Bomb> bomb)
{
    /**
    * This method is responsible for checking if any explosions need to be removed
    * 
    * It takes vector of walls and boxes, and vector of bombs
    * 
    * it checks each arm separtly to se if any of explosions colide with wall object
    * if yes this explosion is registered as one that needs to be deleted and every explosion
    * after that one in same arm is also registered be deleted
    * At the same time algorithm chacks if tere are any boxes in the explosion if yes 
    * hit method of boxes is called
    * After each arm is checked explosions that need to be deleted are removed from explosions_ vector
    */
    explosions_on_board_++;
    int bomb_pos_x = bomb->position().x;
    int bomb_pos_y = bomb->position().y;
    std::vector<int> explosionc_to_destroy;
    std::vector<bool> eplosion_not_stopped = { true, true, true, true };
    for (int i = 0; i < bomb->radius(); i++)
    {
        if (eplosion_not_stopped[0])
        {
            for (int j = 0; j < game_board_->items().size(); j++)
            {
                if ((game_board_->items()[j]->position().x > bomb_pos_x - GRID_SLOT_SIZE * bomb->radius() || game_board_->items()[j]->position().x < bomb_pos_x + GRID_SLOT_SIZE * bomb->radius()) &&
                (game_board_->items()[j]->position().y > bomb_pos_y - GRID_SLOT_SIZE * bomb->radius() || game_board_->items()[j]->position().y < bomb_pos_y + GRID_SLOT_SIZE * bomb->radius()))
                {
                    if (explosions_[explosions_on_board_ - 1 +4*i+1]->get_global_bounds().intersects(game_board_->items()[j]->get_global_bounds()) && not std::dynamic_pointer_cast<Box>(items_on_b[j]))
                    {
                        eplosion_not_stopped[0] = false;
                        explosionc_to_destroy.push_back(explosions_on_board_ + 4*i);
                    }
                    else if (explosions_[explosions_on_board_ - 1 + 4 * i + 1]->get_global_bounds().intersects(game_board_->items()[j]->get_global_bounds()) && std::dynamic_pointer_cast<Box>(items_on_b[j]))
                    {
                        auto box = std::dynamic_pointer_cast<Box>(game_board_->items()[j]);
                        if (box->hit(bomb->strength()))
                        {
                            game_board_->remove_item(j);
                            j--;
                        }
                    }
                }
            }
        }
        else
        {
            explosionc_to_destroy.push_back(explosions_on_board_ - 1 + 4*i+1);
        }

        if (eplosion_not_stopped[1])
        {
            for (int j = 0; j < game_board_->items().size(); j++)
            {
                if ((game_board_->items()[j]->position().x > bomb_pos_x - GRID_SLOT_SIZE * bomb->radius() || game_board_->items()[j]->position().x < bomb_pos_x + GRID_SLOT_SIZE * bomb->radius()) &&
                    game_board_->items()[j]->position().y > bomb_pos_y - GRID_SLOT_SIZE * bomb->radius() || game_board_->items()[j]->position().y < bomb_pos_y + GRID_SLOT_SIZE * bomb->radius())
                {
                    if (explosions_[explosions_on_board_ - 1 + 4 * i + 2]->get_global_bounds().intersects(game_board_->items()[j]->get_global_bounds()) && not std::dynamic_pointer_cast<Box>(game_board_->items()[j]))
                    {
                        eplosion_not_stopped[1] = false;
                        explosionc_to_destroy.push_back(explosions_on_board_ - 1 + 4 * i + 2);
                    }
                    else if (explosions_[explosions_on_board_ - 1 + 4 * i + 2]->get_global_bounds().intersects(game_board_->items()[j]->get_global_bounds()) && std::dynamic_pointer_cast<Box>(game_board_->items()[j]))
                    {
                        auto box = std::dynamic_pointer_cast<Box>(game_board_->items()[j]);
                        if (box->hit(bomb->strength()))
                        {
                            game_board_->remove_item(j);
                            j--;
                        }
                    }
                }
            }
        }
        else
        {
            explosionc_to_destroy.push_back(explosions_on_board_ - 1 + 4 * i + 2);
        }

        if (eplosion_not_stopped[2])
        {
            for (int j = 0; j < game_board_->items().size(); j++)
            {
                if ((game_board_->items()[j]->position().x > bomb_pos_x - GRID_SLOT_SIZE * bomb->radius() || game_board_->items()[j]->position().x < bomb_pos_x + GRID_SLOT_SIZE * bomb->radius()) &&
                    game_board_->items()[j]->position().y > bomb_pos_y - GRID_SLOT_SIZE * bomb->radius() || game_board_->items()[j]->position().y < bomb_pos_y + GRID_SLOT_SIZE * bomb->radius())
                {
                    if (explosions_[explosions_on_board_ - 1 + 4 * i + 3]->get_global_bounds().intersects(game_board_->items()[j]->get_global_bounds()) && not std::dynamic_pointer_cast<Box>(game_board_->items()[j]))
                    {
                        eplosion_not_stopped[2] = false;
                        explosionc_to_destroy.push_back(explosions_on_board_ - 1 + 4 * i + 3);
                    }
                    else if (explosions_[explosions_on_board_ - 1 + 4 * i + 3]->get_global_bounds().intersects(game_board_->items()[j]->get_global_bounds()) && std::dynamic_pointer_cast<Box>(game_board_->items()[j]))
                    {
                        auto box = std::dynamic_pointer_cast<Box>(game_board_->items()[j]);
                        if (box->hit(bomb->strength()))
                        {
                            game_board_->remove_item(j);
                            j--;
                        }
                    }
                }
            }
        }
        else
        {
            explosionc_to_destroy.push_back(explosions_on_board_ - 1 + 4 * i + 3);
        }

        if (eplosion_not_stopped[3])
        {
            for (int j = 0; j < game_board_->items().size(); j++)
            {
                std::shared_ptr<Box> box;
                if ((game_board_->items()[j]->position().x > bomb_pos_x - GRID_SLOT_SIZE * bomb->radius() || game_board_->items()[j]->position().x < bomb_pos_x + GRID_SLOT_SIZE * bomb->radius()) &&
                    game_board_->items()[j]->position().y > bomb_pos_y - GRID_SLOT_SIZE * bomb->radius() || game_board_->items()[j]->position().y < bomb_pos_y + GRID_SLOT_SIZE * bomb->radius())
                {
                    if (explosions_[explosions_on_board_ -1 + 4 * i + 4]->get_global_bounds().intersects(game_board_->items()[j]->get_global_bounds()) && not std::dynamic_pointer_cast<Box>(game_board_->items()[j]))
                    {
                        eplosion_not_stopped[3] = false;
                        explosionc_to_destroy.push_back(explosions_on_board_ - 1 + 4*i+4);
                    }
                    else if (explosions_[explosions_on_board_ - 1 + 4 * i + 4]->get_global_bounds().intersects(game_board_->items()[j]->get_global_bounds()) && std::dynamic_pointer_cast<Box>(game_board_->items()[j]))
                    {
                        auto box = std::dynamic_pointer_cast<Box>(game_board_->items()[j]);
                        if (box->hit(bomb->strength()))
                        {
                            game_board_->remove_item(j);
                            j--;
                        }
                    }
                }
            }
        }
        else
        {
            explosionc_to_destroy.push_back(explosions_on_board_ - 1 + 4*i + 4);
        }
    }
    for (int j = explosionc_to_destroy.size() - 1; j >= 0; j--)
    {
        explosions_.erase(explosions_.begin() + explosionc_to_destroy[j]);
    }
    explosions_on_board_ = explosions_.size();

}

bool Game::check_explosion_(bool versus)
{
    for (int i = 0; i < explosions_.size(); i++)
    {
        if (explosions_[i]->did_end())
        {
            explosions_.erase(explosions_.begin() + i);
            i--;
            explosions_on_board_--;
        }
    }
    for (auto explosion : explosions_)
    {
        for(int i = 0; i<enemies_.size(); i++)
        if (explosion->get_global_bounds().intersects(enemies_[i]->get_global_bounds()))
        {
            enemies_.erase(enemies_.begin() + i);
            i--;
        }
    }
    for (auto player : players_)
    {
        for (int i = 0; i < explosions_.size(); i++)
        {
            if (explosions_[i]->get_global_bounds().intersects(player->get_global_bounds()))
            {
                explosions_.clear();
                explosions_on_board_ = 0;
                if (versus)
                {
                    player->set_hp(player->get_hp() - 1);
                }
                return true;
            }
        }
    }
    return false;
}

bool Game::kill_players_(int pixels_moved, bool versus)
{
    if (check_enemies_())
    {
        shift_game_board_(pixels_moved, 3);
        for (auto player : players_)
        {
            player->set_position({ 0, 0 });
            player->set_hp(player->get_hp() - 1);
        }
        return true;
    }
    if (check_explosion_(versus))
    {
        shift_game_board_(pixels_moved, 3);
        for (auto player : players_)
        {
            if (not versus)
            {
                player->set_position({ 0, 0 });
                player->set_hp(player->get_hp() - 1);
            }
        }
        return true;
    }
    return false;
}

bool Game::check_enemies_()
{
    for (int i = 0; i < enemies_.size(); i++)
    {
        for (std::shared_ptr<Player> player : players_)
        {
            if (player->get_global_bounds().intersects(enemies_[i]->get_global_bounds()))
            {
                return true;
            }
        }
    }
    return false;
}

void Game::display_player_move_sideways_(std::shared_ptr<Player> player, int multiplier)
{
    int texture_number;
    int player_number = -1;
    int add_text_pos = 0;
    if (multiplier == -1)
    {
        add_text_pos = 2;
    }
    for (int i = 0; i < players_.size(); i++)
    {
        if (player == players_[i] && player->can_textured_be_placed(50))
        {
            player_number = i;
            if (player->get_last_texture_number() == 1)
            {
                texture_number = 0;
                player->set_last_texture_number(0);
            }
            else
            {
                texture_number = 1;
                player->set_last_texture_number(1);
            }
        }
    }
    if (player_number == 0)
    {
        std::string path = PLAYER_MOVE_SIDEWAYS[texture_number+add_text_pos];
        if (!player1_texture_.loadFromFile(path))
        {
            throw (FliePathException());
        }
        player->place_texture();
    }
    else if (player_number == 1)
    {
        std::string path = PLAYER_MOVE_SIDEWAYS[texture_number];
        if (!player2_texture_.loadFromFile(path))
        {
            throw (FliePathException());
        }
        player->place_texture();
    }
}

void Game::display_player_move_forward_(std::shared_ptr<Player> player)
{
    int texture_number;
    int player_number = -1;
    for (int i = 0; i < players_.size(); i++)
    {
        if (player == players_[i] && player->can_textured_be_placed(50))
        {
            player_number = i;
            if (player->get_last_texture_number() == 1)
            {
                texture_number = 0;
                player->set_last_texture_number(0);
            }
            else
            {
                texture_number = 1;
                player->set_last_texture_number(1);
            }
        }
    }
    if (player_number == 0)
    {
        std::string path = PLAYER_MOVE_FORWARD[texture_number];
        if (!player1_texture_.loadFromFile(path))
        {
            throw (FliePathException());
        }
        player->place_texture();
    }
    else if (player_number == 1)
    {
        std::string path = PLAYER_MOVE_FORWARD[texture_number];
        if (!player2_texture_.loadFromFile(path))
        {
            throw (FliePathException());
        }
        player->place_texture();
    }
}

void Game::display_player_move_backward_(std::shared_ptr<Player> player)
{
    display_player_move_forward_(player);
}

void Game::generate_enemies_()
{
    srand(time(NULL));
    int number_of_enemies = rand() % (10 - 5 + 1) + 5;
    float pos_y;
    float pos_x;
    bool is_coliding = false;
    for(int i = 0; i<number_of_enemies; i++)
    {
        enemies_.push_back(std::make_shared<Enemy>(Enemy({ 1, 1 }, TEXTURE_SCALE, enemy_texture_)));
        do
        {
            is_coliding = false;
            pos_x = (rand() % (STORY_SIZE[0] - 5) + 5)*GRID_SLOT_SIZE;
            pos_y = (rand() % STORY_SIZE[1])*GRID_SLOT_SIZE;
            for (auto item : game_board_->items())
            {
                if (item->position().x == pos_x && item->position().y == pos_y)
                {
                    is_coliding = true;
                    break;
                }
            }
        } while (is_coliding);
        enemies_[i]->set_position({ pos_x+GRID_SLOT_SIZE/4, pos_y+GRID_SLOT_SIZE/4 });
    }
}

void Game::draw_score_(sf::RenderWindow& window, int points)
{
    sf::Text score;
    sf::Font font;
    float size = 40;
    if (!font.loadFromFile(FONT_PATH))
    {
        throw FliePathException();
    }
    score.setString("Score: " + std::to_string(points));
    score.setCharacterSize(size);
    score.setFillColor(sf::Color::Black);
    score.setStyle(sf::Text::Bold);
    score.setPosition({ .5f*size, window.getSize().y - 1.5f*size});
    score.setFont(font);
    window.draw(score);
}

void Game::draw_game_(sf::RenderWindow& window)
{
    game_board_->draw_to(window);
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
    for (auto enemy : enemies_)
    {
        enemy->draw_to(window);
    }
}

void Game::draw_result_(sf::RenderWindow& window)
{
    sf::Text result;
    sf::Font font;
    float size = 80;
    if (!font.loadFromFile(FONT_PATH))
    {
        throw FliePathException();
    }
    if (players_[0]->get_hp() > players_[1]->get_hp())
    {
        result.setString("Player 1 won");
    }
    else
    {
        result.setString("Player 2 won");
    }

    result.setCharacterSize(size);
    result.setStyle(sf::Text::Bold);
    result.setFillColor(sf::Color::Black);
    result.setPosition({ window.getSize().x*0.5f - 2.5f * size , window.getSize().y * 0.5f - 0.5f*size });
    result.setFont(font);
    window.draw(result);
    window.display();
    sf::Event event;
    while (true)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                exit(1);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                return;
            }
        }
    }
}

bool Game::check_if_players_are_dead_()
{
    for (auto player : players_)
    {
        if (player->get_hp() <= 0)
        {
            return true;
        }
    }
    return false;
}

void Game::display_level_statistic_(int level_points, int boxes, int enemies, sf::RenderWindow& window)
{
    sf::Text result;
    sf::Text result2;
    sf::Text result3;
    sf::Font font;
    float size = 80;
    if (!font.loadFromFile(FONT_PATH))
    {
        throw FliePathException();
    }
    window.clear(sf::Color(69, 159, 66));
    result.setString("Level points: " + std::to_string(level_points));
    result.setPosition({ window.getSize().x * 0.5f - 3.f * size , window.getSize().y * 0.5f - 1.5f * size - 10 });
    result.setCharacterSize(size);
    result.setStyle(sf::Text::Bold);
    result.setFillColor(sf::Color::Black);
    result.setFont(font);
    window.draw(result);
    result2.setString("Boxes destroied: " + std::to_string(boxes));
    result2.setPosition({ window.getSize().x * 0.5f - 3.f * size , window.getSize().y * 0.5f - 0.5f * size });
    result2.setCharacterSize(size);
    result2.setStyle(sf::Text::Bold);
    result2.setFillColor(sf::Color::Black);
    result2.setFont(font);
    window.draw(result2);
    result3.setString("Enemies kiled: " + std::to_string(enemies));
    result3.setPosition({ window.getSize().x * 0.5f - 3.f * size , window.getSize().y * 0.5f + 0.5f * size + 10 });
    result3.setCharacterSize(size);
    result3.setStyle(sf::Text::Bold);
    result3.setFillColor(sf::Color::Black);
    result3.setFont(font);
    window.draw(result3);
    sf::Event event;
    window.display();
    bool run_stop = true;
    while (run_stop)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased)
            {
                run_stop = false;
            }
        }
    }
    while (true)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                exit(1);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                return;
            }
        }
    }
}

void Game::move_enemies_()
{
    for (auto enemy : enemies_)
    {
        enemy->move(game_board_->items());
    }
}
