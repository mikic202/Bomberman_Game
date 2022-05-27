#include "MainMenu.h"
//TODO DELETE NAMESPACE
using namespace std;


// TODO MAKE EXCEPTION WHEN BACKGROUND IMAGE IS NOT FOUND
MainMenu::MainMenu()
{
	// Menu fields
	this->play = new sf::Text();
	this->scores = new sf::Text();
	this->credits = new sf::Text();
	this->exit = new sf::Text();
	this->play->setString("Play!");
	this->scores->setString("Scores");
	this->credits->setString("Credits");
	this->exit->setString("Exit");
	this->menu_fields = { play, scores, credits, exit };

	//this->menu_fields.push_back(play);
	//this->menu_fields[0]->setString("Play!");
	//this->menu_fields.push_back(scores);
	//this->menu_fields[1]->setString("Scores");
	//this->menu_fields.push_back(credits);
	//this->menu_fields[2]->setString("Credits");
	//this->menu_fields.push_back(exit);
	//this->menu_fields[3]->setString("Exit");


	this->bottom_menu_field = *(this->menu_fields.end()-1);
	this->top_menu_field = this->menu_fields[0];
	this->target_text = this->top_menu_field;
	// x and y positions for every menu field
	float x_pos = 50.f;
	float current_y_pos = (WINDOW_HEIGHT / 2) - 50;
	for (size_t i = 0; i < menu_fields.size(); i++)
	{
		this->menu_fields[i]->setFillColor(MAIN_MENU_TEXT_COLOR);
		this->menu_fields[i]->setFont(this->font);
		this->menu_fields[i]->setCharacterSize(70);
		//std::cout << WINDOW_WIDTH / 2.f - this->menu_fields[i]->getGlobalBounds().width / 2.f << "\t\t"
		//	<< WINDOW_HEIGHT / 2.f - this->menu_fields[i]->getGlobalBounds().height / 2.f << endl;
		this->menu_fields[i]->setPosition(
			x_pos,
			current_y_pos
		);
		current_y_pos += 70;
	}
	this->target_text->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);

	// Menu background
	if(!this->background_texture.loadFromFile("Assets/main_menu_background.jpg"))
		std::cout << "ERROR DURING LOADING BACKGROUND FOR MAIN MENU\n";
	this->background.setTexture(this->background_texture);
	
}

void MainMenu::clickedField(sf::Text* target_text)
{
	if (this->target_text->getString() == "Exit")
	{
		this->window->close();
	}
	else if(this->target_text->getString() == "Credits")
	{
		CreditsMenu credits_menu;
		this->window->close();
		credits_menu.run();
	}
	else if (this->target_text->getString() == "Scores")
	{
		cout << "scores\n";
	}
	else if (this->target_text->getString() == "Play!")
	{

		cout << "play\n";
	}
}



// If mouse is over and 
void MainMenu::update()
{
	//cout << "UPDATE MAINMENU CALLED\n";
	//this->mouse_update();

	// polling events
	this->poll_events();


}


void MainMenu::render()
{
	this->window->clear();
	//cout << this->menu_fields.size();
	this->window->draw(this->background);

	render_text_fields();


	//for (size_t i = 0; i < this->menu_fields.size(); i++)
	//{
	//	this->window->draw(*this->menu_fields[i]);
	//}

	this->window->display();
}



void MainMenu::render_text_fields()
{
	for (size_t i = 0; i < this->menu_fields.size(); i++)
	{
		this->window->draw(*this->menu_fields[i]);
	}
}

MainMenu::~MainMenu()
{
	std::cout << "DESTRUCTOR OF MAINMENU CALLED\n";
}





