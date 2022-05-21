#include "Game.h"



void Game::play()
{
    play_story_();
}

void Game::play_story_()
{
    sf::RenderWindow window(sf::VideoMode(1600, 700), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Bomb bomb({ 10, 10 }, 5, 6, 6, { 0.5, 0.5 });

    //sf::Sprite item_sprite_;
    //sf::Texture item_texture;

    VersusModeBoard board(20);
    StoryModeBoard story_b_(12, 1);


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
        story_b_.draw_to(window);
        //bomb.draw_to(window);
        //window.draw(bomb.item_sprite_);
        //window.draw(item_sprite_);
        //window.draw(shape);
        window.display();
    }

    return;
}