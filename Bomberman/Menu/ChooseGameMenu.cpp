#include "ChooseGameMenu.h"

ChooseGameMenu::ChooseGameMenu(char type, bool new_game)
{
	this->count_saved = 0;
	this->type = type;
	this->new_game = new_game;
	this->go_back = new sf::Text("Go back", this->font, 60);
	this->go_back->setPosition(
		WINDOW_WIDTH / 2.f - this->go_back->getGlobalBounds().width / 2.f,
		WINDOW_HEIGHT- 70);
	this->go_back->setFillColor(MAIN_MENU_TEXT_COLOR);
	if (type == 'C')
		count_saved = CO_OP_SAVES.size();
	else if (type == 'S')
		count_saved = STORY_SAVES.size();
	std::string name = "";
	if (new_game)
		name = "New game ";
	else
		name = "Load game ";

	float y_pos = 200;
	for (size_t i = 0; i < count_saved; i++)
	{
		sf::Text* temp_text = new sf::Text(name + std::to_string(i+1), this->font, 60);
		float x_pos = WINDOW_WIDTH / 2.f - temp_text->getGlobalBounds().width / 2.f;
		temp_text->setPosition(x_pos, y_pos);
		menu_fields.push_back(temp_text);
		menu_fields[i]->setFillColor(MAIN_MENU_TEXT_COLOR);
		y_pos += 90;
	}
	menu_fields.push_back(go_back);
	this->top_menu_field = *menu_fields.begin();
	this->bottom_menu_field = *(menu_fields.end()-1);
	this->target_text = this->top_menu_field;
	this->target_text->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);

}

void ChooseGameMenu::poll_events()
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
			if (ev.key.code == sf::Keyboard::Escape)
			{
				ChooseModeMenu mode_menu(this->type);
				this->window->close();
				mode_menu.run();
			}

			if (ev.key.code == sf::Keyboard::Enter)
				clickedField(this->target_text);
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
				std::cout << 1;
				//this->pop_up_menu->show();

			break;
		}
		// mouse polling events
		mouse_update();

	}
}

void ChooseGameMenu::clickedField(sf::Text* target_text)
{
	if (target_text->getString() == "Go back")
	{
		ChooseModeMenu choose_mode_menu(this->type);
		this->window->close();
		choose_mode_menu.run();
	}
	else
	{
		Game game;
		sf::RenderWindow window(sf::VideoMode(this->window->getSize().x, this->window->getSize().y), "Bomberman");
		this->window->close();
		std::cout <<  "New game: " << this->get_target_number() << std::endl;

		game.play( get_target_number(), type, new_game, window);
	}
}

// Return index of game saved choosen
int ChooseGameMenu::get_target_number()
{
	// convert last char in target_text to int 
	int num = int(*(this->target_text->getString().end() - 1)) - 48;

	return num;
}



void ChooseGameMenu::render()
{

	this->window->clear(CHOOSE_MODE_MENU_COLOR);

	render_menu_fields();

	this->window->display();
}

void ChooseGameMenu::render_menu_fields()
{
	for (size_t i = 0; i < this->menu_fields.size(); i++)
	{
		this->window->draw(*this->menu_fields[i]);
	}
}

ChooseGameMenu::~ChooseGameMenu()
{

}