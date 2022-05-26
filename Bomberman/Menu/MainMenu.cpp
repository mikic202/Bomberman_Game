#include "MainMenu.h"
//TODO DELETE NAMESPACE
using namespace std;

MainMenu::MainMenu()
{
	this->play = new sf::Text();
	this->scores = new sf::Text();
	this->credits = new sf::Text();
	this->exit = new sf::Text();
	this->menu_fields.push_back(play);
	this->menu_fields[0]->setString("Play!");
	this->menu_fields.push_back(scores);
	this->menu_fields[1]->setString("Scores");
	this->menu_fields.push_back(credits);
	this->menu_fields[2]->setString("Credits");
	this->menu_fields.push_back(exit);
	this->menu_fields[3]->setString("Exit");

	for (size_t i = 0; i < menu_fields.size(); i++)
	{
		this->menu_fields[i]->setFillColor(sf::Color::Red);
		this->menu_fields[i]->setFont(this->font);
		this->menu_fields[i]->setCharacterSize(30);
		//std::cout << WINDOW_WIDTH / 2.f - this->menu_fields[i]->getGlobalBounds().width / 2.f << "\t\t"
		//	<< WINDOW_HEIGHT / 2.f - this->menu_fields[i]->getGlobalBounds().height / 2.f << endl;
		this->menu_fields[i]->setPosition(
			WINDOW_WIDTH / 2.f - this->menu_fields[i]->getGlobalBounds().width / 2.f,
			WINDOW_HEIGHT / 2.f - this->menu_fields[i]->getGlobalBounds().height / 2.f
			);
	}




}

void MainMenu::clickedField(sf::Text* target_text)
{
}


//void MainMenu::run()
//{
//	while (this->window->isOpen())
//	{
//		//cout << "d";
//		
//		this->update();
//		this->render();
//
//
//
//	}
//}

void MainMenu::update()
{
	cout << "UPDATE MAINMENU CALLED\n";
	// polling events
	this->poll_events();
}

void MainMenu::render()
{
	this->window->clear();
	//cout << this->menu_fields.size();

	for (size_t i = 0; i < this->menu_fields.size(); i++)
	{
		this->window->draw(*this->menu_fields[i]);
	}
	this->window->draw(this->test);

	this->window->display();
}

MainMenu::~MainMenu()
{
	std::cout << "DESTRUCTOR OF MAINMENU CALLED\n";
}





