#include "Game.h"
#include <SFML/Graphics.hpp>
#include"../Items/Bomb.h"
#include "../Game Board/StoryModeBoard.h"
#include "../Game Board/VersusModeBoard.h"
#include "../Items/Box.h"


void Game::game()
{
    sf::RenderWindow window(sf::VideoMode(1600, 700), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Bomb bomb({ 10, 10 }, 5, 6, 6, { 0.5, 0.5 });

    //sf::Sprite item_sprite_;
    //sf::Texture item_texture;

    VersusModeBoard board(20);
    StoryModeBoard board2(12, 1);


    std::cout << "a";
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        board2.draw_to(window);
        //bomb.draw_to(window);
        //window.draw(bomb.item_sprite_);
        //window.draw(item_sprite_);
        //window.draw(shape);
        window.display();
    }

    return ;
}