#pragma once
#include "Menu.h"
#include "MainMenu.h"
#include "ChooseModeMenu.h"
#include "../Game/Game.h"

// Class representing menu for choosing in which file game will be saved
class ChooseGameMenu : public Menu
{
public:
	ChooseGameMenu(char type, bool new_game);
	virtual void clickedField(sf::Text* target_text) override;

	// Return number of saving for current target_field
	int get_target_number();


	void poll_events() override;

	void render_menu_fields();
	void render() override;

	~ChooseGameMenu();

private:
	char type;
	bool new_game;
	unsigned int count_saved;
	sf::Text* go_back;

};

