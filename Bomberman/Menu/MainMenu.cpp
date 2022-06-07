#include "MainMenu.h"

MainMenu::MainMenu()
{
	// Menu fields
	this->play_story = new sf::Text();
	this->play_coop = new sf::Text();
	this->scores = new sf::Text();
	this->credits = new sf::Text();
	this->exit = new sf::Text();
	this->play_versus = new sf::Text();
	this->play_story->setString("Play Story!");
	this->play_coop->setString("Play Cooperative!");
	this->scores->setString("Scores");
	this->credits->setString("Credits");
	this->exit->setString("Exit");
	this->play_versus->setString("Play Versus!");
	this->menu_fields = { play_story, play_coop, play_versus, scores, credits, exit };



	this->bottom_menu_field = *(this->menu_fields.end()-1);
	this->top_menu_field = this->menu_fields[0];
	this->target_text = this->top_menu_field;

	// x and y positions for every menu field
	float x_pos = 50.f;
	float current_y_pos = (WINDOW_HEIGHT / 2) - 80;
	for (size_t i = 0; i < menu_fields.size(); ++i)
	{
		this->menu_fields[i]->setFillColor(MAIN_MENU_TEXT_COLOR);
		this->menu_fields[i]->setFont(this->font);
		this->menu_fields[i]->setCharacterSize(70);
		this->menu_fields[i]->setPosition(
			x_pos,
			current_y_pos
		);
		current_y_pos += 60;
	}
	this->target_text->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);

	// Menu background
	if (!this->background_texture.loadFromFile("Assets/main_menu_background.jpg"))
		throw MenuBackgroundCanNotBeEmpty("Can not load backgrround texture for MainMenu!");
	this->background.setTexture(this->background_texture);
	
}

void MainMenu::clickedField(sf::Text* target_text)
{
	if (this->target_text->getString() == "Exit")
		this->window->close();
	else if(this->target_text->getString() == "Credits")
	{
		CreditsMenu credits_menu;
		this->window->close();
		credits_menu.run();
	}
	else if (this->target_text->getString() == "Scores"){ /* Will be added in the future! */ }
	else if (this->target_text->getString() == "Play Story!")
	{
		ChooseModeMenu choose_mode_menu('S');
		this->window->close();
		choose_mode_menu.run();
		this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bomberman");
	}
	else if (this->target_text->getString() == "Play Cooperative!")
	{
		ChooseModeMenu choose_mode_menu('C');
		this->window->close();
		choose_mode_menu.run();
		this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bomberman");
	}
	else if (this->target_text->getString() == "Play Versus!")
	{
		this->window->close();
		sf::RenderWindow game_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bomberman");
		Game game;
		game.play(1, 'V', true, game_window);
		this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bomberman");
	}
}

void MainMenu::update()
{
	// polling events
	this->poll_events();
}

// draw all content of menu on window
void MainMenu::render()
{
	this->window->clear();
	this->window->draw(this->background);

	render_text_fields();
	this->window->display();
}


// drawing menu fields on window
void MainMenu::render_text_fields()
{
	for (size_t i = 0; i < this->menu_fields.size(); i++)
	{
		this->window->draw(*this->menu_fields[i]);
	}
}

MainMenu::~MainMenu()
{
	if (this->window != nullptr)
		delete this->window;
}





