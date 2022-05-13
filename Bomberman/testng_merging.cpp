//#include <SFML/Graphics.hpp>
//#include"Items/Bomb.h"
//#include "Game Board/StoryModeBoard.h"
//#include "Game Board/GameBoard.h"
//#include "Items/Box.h"
//
//int main()
//{
//    sf::RenderWindow window(sf::VideoMode(700, 700), "SFML works!");
//    sf::CircleShape shape(100.f);
//    shape.setFillColor(sf::Color::Green);
//    Bomb bomb({ 10, 10 }, 5, 6, 6, {0.5, 0.5});
//
//    //sf::Sprite item_sprite_;
//    //sf::Texture item_texture;
//
//    StoryModeBoard board(2, 1);
//    
//
//    std::cout << "a";
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//
//        window.clear();
//        board.draw_to(window);
//        //bomb.draw_to(window);
//        //window.draw(bomb.item_sprite_);
//        //window.draw(item_sprite_);
//        //window.draw(shape);
//        window.display();
//    }
//
//    return 0;
//}