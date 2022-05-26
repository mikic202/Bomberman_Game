#pragma once
#include "Menu.h"
class MainMenu : public Menu
{
public:
	MainMenu();
	void clickedField(sf::Text* target_text) override;

	//void run() override;

	void update() override;
	void render() override;
	~MainMenu();
private:
	sf::Text* play;
	sf::Text* scores;
	sf::Text* credits;
	sf::Text* exit;
	sf::Text test;
};

