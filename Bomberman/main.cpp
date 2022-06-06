#include <SFML/Graphics.hpp>
#include"Items/Bomb.h"
#include "Game Board/StoryModeBoard.h"
#include "Game Board/VersusModeBoard.h"
#include "Items/Box.h"
#include "Game/Game.h"
#include "Menu/MainMenu.h"

int main()
{
	MainMenu* mainmenu = new MainMenu();
	mainmenu->run();
	delete mainmenu;

}