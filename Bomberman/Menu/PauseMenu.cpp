#include "PauseMenu.h"


PauseMenu::PauseMenu( char type, unsigned int saved_num)
{
	//this->game = game;
	this->type = type;
	this->saved_num = saved_num;
	std::vector<std::string> text_fields_names = { "Continue", "Start new game", "Exit" };
	
	// Y position for every menu field
	float current_pos_y = WINDOW_HEIGHT / 2 - 200;
	for (size_t i = 0; i < text_fields_names.size(); i++)
	{
		sf::Text* temp_text = new sf::Text(text_fields_names[i], this->font, 70);
		temp_text->setPosition(
			WINDOW_WIDTH / 2 - temp_text->getGlobalBounds().width / 2,
			current_pos_y);
		temp_text->setFillColor(MAIN_MENU_TEXT_COLOR);
		this->menu_fields.push_back(temp_text);
		current_pos_y += 100;
	}
	this->top_menu_field = *menu_fields.begin();
	this->bottom_menu_field = *(menu_fields.end() - 1);
	this->target_text = this->top_menu_field;
	this->target_text->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);
}

//TODO logic
void PauseMenu::clickedField(sf::Text* target_text)
{
	if (target_text->getString() == "Continue")
	{
		std::cout << "cont\n";
	}
	else if (target_text->getString() == "Start new game")
	{
		//Game game;

		//game.play(saved_num, this->type, true, *this->window);
		std::cout << "new game\n";
	}
	else if (target_text->getString() == "Exit")
	{
		std::cout << "ex\n";
	}
}

//void PauseMenu::poll_events()
//{
//
//}

PauseMenu::~PauseMenu()
{

}
