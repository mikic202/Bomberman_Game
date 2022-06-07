#include "PauseMenu.h"

PauseMenu::PauseMenu( char type, unsigned int saved_num)
{
	this->type = type;
	this->saved_num = saved_num;
	std::vector<std::string> text_fields_names = { "Continue", "Start new game", "Exit" };
	
	// y position for every menu field
	float current_pos_y = WINDOW_HEIGHT / 2 - 200;
	// setting menu fields
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

PauseMenu::PauseMenu(char type, sf::RenderWindow& window, unsigned int saved_num) : PauseMenu(type, saved_num)
{
	// Because default constructor of Menu is creating window we should delete it firstly
	delete this->window;
	this->window = &window;
}

bool PauseMenu::clickedMenuField(sf::Text* target_text)
{
	if (target_text->getString() == "Continue")
	{
		can_game_continue = true;

	}
	else if (target_text->getString() == "Start new game")
	{
		can_game_continue = false;
	}
	else if (target_text->getString() == "Exit")
	{
		// Close entire program
		this->window->close();
		exit(1);

	}
	is_menu_open = false;
	return false;
}

void PauseMenu::poll_events()
{
	sf::Event ev;

	while (this->window->pollEvent(ev) && this->is_menu_open)
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse_over(menu_fields[i]))
		{
			clickedMenuField(menu_fields[i]);
			break;
		}
		if (mouse_over(menu_fields[i]))
		{
			target_text->setFillColor(MAIN_MENU_TEXT_COLOR);
			target_text = menu_fields[i];
			target_text->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);
			break;
		}
	}
}

bool PauseMenu::get_can_game_continue() { return this->can_game_continue; }
void PauseMenu::set_is_menu_open(bool value) { this->is_menu_open = value; }

PauseMenu::~PauseMenu() { }
