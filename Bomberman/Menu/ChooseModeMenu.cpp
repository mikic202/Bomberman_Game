#include "ChooseModeMenu.h"

ChooseModeMenu::ChooseModeMenu(char type)
{
	//type
	this->type = type;
	
	// background
	if(!this->background_texture.loadFromFile("Assets/choose_mode_background.jpg"))
		throw MenuBackgroundCanNotBeEmpty("Can not load backgrround texture for ChooseModeMenu!");
	this->background.setTexture(this->background_texture);
	
	// text fields
	this->new_game = new sf::Text("New game", this->font, 70);
	this->load_game = new sf::Text("Load game", this->font, 70);
	this->go_back = new sf::Text("Return to main menu", this->font, 70);
	this->top_menu_field = new_game;
	this->bottom_menu_field = go_back;
	this->menu_fields = { new_game, load_game, go_back};
	for (size_t i = 0; i < menu_fields.size(); i++)
		this->menu_fields[i]->setFillColor(MAIN_MENU_TEXT_COLOR);
	
	// Position of text fields
	this->new_game->setPosition(60, WINDOW_HEIGHT / 2.f - 60);
	this->load_game->setPosition(WINDOW_WIDTH - 200 - load_game->getGlobalBounds().width / 2,
		this->new_game->getPosition().y);
	this->go_back->setPosition(
		WINDOW_WIDTH / 2.f - go_back->getGlobalBounds().width / 2.f,
		WINDOW_HEIGHT - 100);

	// target text
	this->target_text = top_menu_field;
	target_text->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);
}


void ChooseModeMenu::clickedField(sf::Text* target_text)
{
	if (this->target_text->getString() == "New game")
	{
		ChooseGameMenu choose_game_menu(type, true);
		this->window->close();
		choose_game_menu.run();
	}
	else if (this->target_text->getString() == "Load game")
	{
		ChooseGameMenu choose_game_menu(type, false);
		this->window->close();
		choose_game_menu.run();
	}
	else if (this->target_text->getString() == "Return to main menu")
	{
		MainMenu main_menu;
		this->window->close();
		main_menu.run();
	}
}

void ChooseModeMenu::render_text_fields()
{
	for (size_t i = 0; i < this->menu_fields.size(); i++)
	{
		this->window->draw(*this->menu_fields[i]);
	}
}

void ChooseModeMenu::poll_events()
{
	sf::Event ev;


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
				MainMenu main_menu;
				this->window->close();
				main_menu.run();
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

			break;
		default:
			break;
		}
		// mouse polling events
		mouse_update();

	}
}

void ChooseModeMenu::render()
{
	this->window->clear();
	this->window->draw(this->background);

	render_text_fields();
	this->window->display();
}

ChooseModeMenu::~ChooseModeMenu()
{
	if (this->window != nullptr)
		delete this->window;
}
