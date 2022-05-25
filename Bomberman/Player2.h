#pragma once
#include <SFML/Graphics.hpp>


class Player2
{
public:
    Player2(sf::Vector2f size, sf::Texture& texture)
    {
        player.scale(size);
        player.setTexture(texture);
        //player.setFillColor(sf::Color::Green);
    }

    void draw_to(sf::RenderWindow& window)
    {
        window.draw(player);
    }
    void move(sf::Vector2f distance)
    {
        player.move(distance);
    }
    void set_position(sf::Vector2f position)
    {
        player.setPosition(position);
    }

    int getX() {
        return player.getPosition().x;
    }

    int getY() {
        return player.getPosition().y;
    }

    sf::FloatRect get_global_bounds()
    {
        return player.getGlobalBounds();
    }

    sf::Vector2f size()
    {
        return { 113 *TEXTURE_SCALE.x, 253*TEXTURE_SCALE.y };
    }

private:
    sf::Sprite player;
};