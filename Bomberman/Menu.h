#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define Max_main_menu 4
class Menu
{
public:
	Menu(float width, float height);

	void draw(RenderWindow& window);
	void moveUp();
	void moveDown();

	int mainMenuPressed()
	{
		return MainMenuSelected;
	}
	~Menu();

private:
	int MainMenuSelected;
	Font font;
	Text mainMenu[Max_main_menu];


};

