#include <SFML/Graphics.hpp>
#include"Items/Bomb.h"
#include "Game Board/StoryModeBoard.h"
#include "Game Board/VersusModeBoard.h"
#include "Items/Box.h"
#include "Game/Game.h"
#include "Menu/MainMenu.h"

int main()
{
	//Game game;

	//sf::RenderWindow window(sf::VideoMode(1000, 600), "Bomberman");
	//game.play(1, 'C', true, window);
	MainMenu* mainmenu = new MainMenu();
	mainmenu->run();
	delete mainmenu;
	std::cout << "Ended main\n";

}