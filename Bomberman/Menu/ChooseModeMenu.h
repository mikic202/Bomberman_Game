#pragma once
#include "Menu.h"
#include "MainMenu.h"
#include "ChooseGameMenu.h"
// For chhosing new game or load game from file
class ChooseModeMenu : public Menu
{
public:
	ChooseModeMenu(char type);

	void clickedField(sf::Text* target_text) override;
	virtual void render_text_fields();

	void poll_events() override;
	void render() override;
	~ChooseModeMenu();
private:
	char type;
	sf::Text* new_game;
	sf::Text* load_game;
	sf::Text* go_back;
};


