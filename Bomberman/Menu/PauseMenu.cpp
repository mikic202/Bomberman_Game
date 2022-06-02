#include "PauseMenu.h"

//TODO logic
bool PauseMenu::clickedMenuField(sf::Text* target_text)
{
	std::cout << "s\n";
	if (target_text->getString() == "Continue")
	{
		return true;
		std::cout << "cont\n";

	}
	else if (target_text->getString() == "Start new game")
	{
		Game game;

		game.play(saved_num, this->type, true, *this->window);
		std::cout << "new game\n";
	}
	else if (target_text->getString() == "Exit")
	{
		// EXIT PROGRAM
		this->window->close();
		exit(1);

		std::cout << "ex\n";
	}
	return false;
}


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

void PauseMenu::poll_events()
{
	sf::Event ev;
	//std::cout << string(this->target_text->getString()) << endl;


	while (this->window->pollEvent(ev))
	{
		// Keyboard polling events
		sf::Time elapsed_time = menu_clock.getElapsedTime();
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Enter)
				this->clickedMenuField(target_text);
			if (ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::W)
				if (elapsed_time.asSeconds() > MENU_CHANGE_FIELD_COOLDOWN_SECONDS)
				{
					move_up();
					menu_clock.restart();
				}
			if (ev.key.code == sf::Keyboard::Down || ev.key.code == sf::Keyboard::S)
				if (elapsed_time.asSeconds() > MENU_CHANGE_FIELD_COOLDOWN_SECONDS)
				{
					move_down();
					menu_clock.restart();
				}
			if (ev.key.code == sf::Keyboard::Escape)
				this->pop_up_menu->show();
			break;
		default:
			break;
		}
		// mouse polling events
		mouse_update();

	}
}



void PauseMenu::mouse_update()
{
	for (size_t i = 0; i < this->menu_fields.size(); i++)
	{
		//std::cout << "CONTAINS\n";
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse_over(menu_fields[i]))
		{
			clickedMenuField(menu_fields[i]);
			break;
		}
		if (mouse_over(menu_fields[i]))
		{
			//menu_fields[i]->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);
			target_text->setFillColor(MAIN_MENU_TEXT_COLOR);
			target_text = menu_fields[i];
			target_text->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);
			break;
		}
	}
}
//void PauseMenu::poll_events()
//{
//
//}



PauseMenu::~PauseMenu()
{

}
