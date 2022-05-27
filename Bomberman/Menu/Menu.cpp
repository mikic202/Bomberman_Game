#include "Menu.h"

//TODO DELETE NAMESPACE STD
using namespace std;
Menu::~Menu()
{
	std::cout << "DESTRUCTOR OF MENU IS CALLED\n";
	delete this->window;
	delete this->pop_up_menu;
	for (size_t i = 0; i < this->menu_fields.size(); i++)
	{
		delete this->menu_fields[i];
	}
}

// TODO EXCEPTION WHEN FONT IS NOT FOUND
void Menu::set_menu_fields(std::vector<sf::Text*> menu_fields)
{
	if (!this->font.loadFromFile(FONT_PATH))
	{
		std::cout << "CANT LOAD FONT FOR MENU\n";
	}
	top_menu_field = *menu_fields.begin();
	bottom_menu_field = *(menu_fields.end()-1);
	target_text = *menu_fields.begin();
	target_text->setFillColor(sf::Color::Red);
}

// TODO 
// EXCEPTION WHEN FONT IS NOT FOUND
Menu::Menu()
{

	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bomberman");
	this->font.loadFromFile(FONT_PATH);
	this->target_text = this->top_menu_field;
}

// TODO EXCEPTION WHEN MENU_FIELDS IS EMPTY
Menu::Menu(float width, float height, std::string name, std::vector<sf::Text*> menu_fields)
{
	if (!this->font.loadFromFile(FONT_PATH))
	{
		std::cout << "CANT LOAD FONT FOR MENU\n";
	}
	if (menu_fields.size() == 0)
	{
		std::cout << "Menu Fields can't be empty!" << std::endl;
	}
	this->window = new sf::RenderWindow(sf::VideoMode(width, height), name);
	for (size_t i = 0; i < menu_fields.size(); ++i)
		this->menu_fields.push_back(menu_fields[i]);
	this->pop_up_menu = nullptr;
	set_menu_fields(this->menu_fields);
}




// TODO POPUPMENU
Menu::Menu(sf::VideoMode video_mode, std::string name, std::vector<sf::Text*> menu_fields, PopUpMenu* pop_up_menu) 
{
	if (!this->font.loadFromFile(FONT_PATH))
	{
		std::cout << "CANT LOAD FONT FOR MENU\n";
	}
	if (menu_fields.size() == 0)
	{
		std::cout << "Menu Fields can't be empty!" << std::endl;
	}
	this->window = new sf::RenderWindow(video_mode, name);
	for (size_t i = 0; i < menu_fields.size(); ++i)
		this->menu_fields.push_back(menu_fields[i]);
	set_menu_fields(menu_fields);
	this->pop_up_menu = pop_up_menu;
}

void Menu::run()
{
	while (this->window->isOpen())
	{
		this->update_clock();
		this->update();

		this->render();

	}
}

bool Menu::mouse_over(sf::Text* text)
{
	//std::cout << bool(text->getGlobalBounds().contains(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y)) << endl;

	return text->getGlobalBounds().contains(sf::Mouse::getPosition(*this->window).x,
		sf::Mouse::getPosition(*this->window).y);
}

void Menu::mouse_update()
{
	for (size_t i = 0; i < this->menu_fields.size(); i++)
	{
		//std::cout << "CONTAINS\n";
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mouse_over(menu_fields[i]))
		{
			clickedField(menu_fields[i]);
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
void Menu::poll_events()
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
				clickedField(this->target_text);
			if (ev.key.code == sf::Keyboard::Up || ev.key.code == sf::Keyboard::W)
				if (elapsed_time.asSeconds() > MENU_CHANGE_FIELD_COOLDOWN_SECONDS)
				{
					move_up();
					menu_clock.restart();
				}
			if (ev.key.code == sf::Keyboard::Down || ev.key.code == sf::Keyboard::S)
				if(elapsed_time.asSeconds() > MENU_CHANGE_FIELD_COOLDOWN_SECONDS)
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

void Menu::update()
{
	// Event polling
	this->poll_events();

}

void Menu::update_clock()
{
	
}

void Menu::render()
{
	//std::cout << menu_fields;
	this->window->clear();
	//this->window->draw(this->background);
	// Draw menu fields
	for (size_t i = 0; i < menu_fields.size(); ++i)
	{	
		//std::cout << "ed";
		//std::cout << menu_fields[i].get()->getPosition().x;
		this->window->draw(*menu_fields[i]);
	}
	this->window->display();

}


void Menu::move_up()
{
	if (this->target_text == *menu_fields.begin())
	{
		this->target_text = (*(menu_fields.end() - 1));
		(*menu_fields.begin())->setFillColor(MAIN_MENU_TEXT_COLOR);
		this->target_text->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);
	}
	else
	{
		for (size_t i = 0; i < this->menu_fields.size(); i++)
		{
			if (this->target_text == menu_fields[i])
			{
				this->target_text = menu_fields[i-1];
				menu_fields[i]->setFillColor(MAIN_MENU_TEXT_COLOR);
				this->target_text->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);
			}
		}
	}
}

void Menu::move_down()
{
	if (this->target_text == (*(menu_fields.end() - 1)))
	{
		this->target_text = (*(menu_fields.begin()));
		(*(menu_fields.end()-1))->setFillColor(MAIN_MENU_TEXT_COLOR);
		this->target_text->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);
	}
	else
	{
		for (size_t i = 0; i < this->menu_fields.size(); i++)
		{
			if (this->target_text == menu_fields[i])
			{
				this->target_text = menu_fields[i + 1];
				menu_fields[i]->setFillColor(MAIN_MENU_TEXT_COLOR);
				this->target_text->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);
				break;
			}
		}
	}
}

bool Menu::menu_field_clicked()
{
	return false;
}
