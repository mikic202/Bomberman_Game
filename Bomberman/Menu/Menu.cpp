#include "Menu.h"
//#include "Menu.h"
//
//Menu::Menu(float width, float height)
//{
//	if (!font.loadFromFile("Pixeboy.ttf"))
//		std::cout << "cant load font\n";
//
//	// Play
//	mainMenu[0].setFont(font);
//	mainMenu[0].setFillColor(Color::White);
//	mainMenu[0].setString("Play");
//	mainMenu[0].setCharacterSize(70);
//	mainMenu[0].setPosition(400, 200);
//
//	// Options
//	mainMenu[1].setFont(font);
//	mainMenu[1].setFillColor(Color::White);
//	mainMenu[1].setString("Options");
//	mainMenu[1].setCharacterSize(70);
//	mainMenu[1].setPosition(400, 300);
//
//	// About
//	mainMenu[2].setFont(font);
//	mainMenu[2].setFillColor(Color::White);
//	mainMenu[2].setString("About");
//	mainMenu[2].setCharacterSize(70);
//	mainMenu[2].setPosition(400, 400);
//
//	//Exit
//	mainMenu[3].setFont(font);
//	mainMenu[3].setFillColor(Color::White);
//	mainMenu[3].setString("EXIT");
//	mainMenu[3].setCharacterSize(70);
//	mainMenu[3].setPosition(400, 500);
//
//	MainMenuSelected = -1;
//
//}

//void Menu::draw(RenderWindow& window)
//{
//	for (size_t i = 0; i < Max_main_menu; ++i)
//	{
//		window.draw(mainMenu[i]);
//	}
//}
//
//void Menu::moveUp()
//{
//	if (MainMenuSelected >= 1)
//	{
//		mainMenu[MainMenuSelected].setFillColor(Color::White);
//		MainMenuSelected--;
//
//		if (MainMenuSelected == -1)
//		{
//			MainMenuSelected = 2;
//		}
//		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
//	}
//}
//
//void Menu::moveDown()
//{
//	if (MainMenuSelected + 1 <= Max_main_menu)
//	{
//		mainMenu[MainMenuSelected].setFillColor(Color::White);
//		MainMenuSelected++;
//
//		if (MainMenuSelected == 4)
//		{
//			MainMenuSelected = 0;
//		}
//		mainMenu[MainMenuSelected].setFillColor(Color::Blue);
//	}
//}
//
//Menu::~Menu()
//{
//
//}




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
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "title");
	this->font.loadFromFile(FONT_PATH);
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
	std::cout << "works;";
	std::cout << this->window->getSize().x;
	while (this->window->isOpen())
	{
		std::cout << "in while\n";
		this->update();

		this->render();

	}
}

void Menu::poll_events()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Enter)
				clickedField(this->target_text);
			if (ev.key.code == sf::Keyboard::Up)
				move_up();
			if (ev.key.code == sf::Keyboard::Down)
				move_down();
			if (ev.key.code == sf::Keyboard::Escape)
				this->pop_up_menu->show();
			break;
		default:
			break;
		}
	}
}

void Menu::update()
{
	// Event polling
	this->poll_events();

}

void Menu::render()
{
	//std::cout << menu_fields;
	this->window->clear();

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
		(*menu_fields.begin())->setFillColor(sf::Color::White);
		this->target_text->setFillColor(sf::Color::Blue);
	}
	else
	{
		for (size_t i = 0; i < this->menu_fields.size(); i++)
		{
			if (this->target_text == menu_fields[i])
			{
				this->target_text = menu_fields[i-1];
				menu_fields[i]->setFillColor(sf::Color::White);
				this->target_text->setFillColor(sf::Color::Blue);
			}
		}
	}
}

void Menu::move_down()
{
	if (this->target_text == (*(menu_fields.end() - 1)))
	{
		this->target_text = (*(menu_fields.begin()));
		(*(menu_fields.end()-1))->setFillColor(sf::Color::White);
		this->target_text->setFillColor(sf::Color::Blue);
	}
	else
	{
		for (size_t i = 0; i < this->menu_fields.size(); i++)
		{
			if (this->target_text == menu_fields[i])
			{
				this->target_text = menu_fields[i + 1];
				menu_fields[i]->setFillColor(sf::Color::White);
				this->target_text->setFillColor(sf::Color::Blue);
			}
		}
	}
}

bool Menu::menu_field_clicked()
{
	return false;
}
