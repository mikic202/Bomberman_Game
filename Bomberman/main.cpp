//Miko³aj Chomanski
//Denys Fokashchuk

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu2/MainMenu.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(825, 825), "Bomberman");
	MainMenu menu;
	menu.open_menu(window);
	//MainMenu* mainmenu = new MainMenu();
	//mainmenu->run();
	//delete mainmenu;
	std::cout << "a";

}