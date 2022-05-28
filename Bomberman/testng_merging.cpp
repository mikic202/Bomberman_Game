#include <SFML/Graphics.hpp>
#include"Items/Bomb.h"
#include "Game Board/StoryModeBoard.h"
#include "Game Board/VersusModeBoard.h"
#include "Items/Box.h"
#include "Game/Game.h"

int main()
{
	Game game;
	sf::RenderWindow window(sf::VideoMode(600, 600), "Bomberman");
	game.play(1, 'C', true, window);
}