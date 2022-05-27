#include "CreditsMenu.h"

// TODO EXCEPTION WHEN BACKGROUND IMAGE CAN'T BE LOADED
CreditsMenu::CreditsMenu()
{
	this->go_back = new sf::Text("Return to main menu", this->font, 60);
	this->main_text = new sf::Text("\t\tMade with \n\tbig patience by\nMikolaj Chomanski\n\t\t\t\tand\nDenys Fokashchuk", this->font, 60);
	this->menu_fields.push_back(go_back);

	this->bottom_menu_field = go_back;
	this->top_menu_field = go_back;

	this->main_text->setFillColor(CREDITS_MENU_TEXT_COLOR);
	this->go_back->setFillColor(MAIN_MENU_TEXT_TARGET_COLOR);
	this->target_text = go_back;
	if (!this->background_texture.loadFromFile("Assets/background_credits.png"))
		std::cout << "ERROR DURING LOADING BACKGROUND FOR CREDITS\n";
	this->background.setTexture(this->background_texture);

	this->main_text->setPosition(
		40,
		40
	);

	this->go_back->setPosition(
		this->window->getSize().x / 2.f - this->go_back->getGlobalBounds().width / 2.f,
		WINDOW_HEIGHT - 100
	);
}

void CreditsMenu::clickedField(sf::Text* target_text)
{
	if (this->target_text->getString() == "Return to main menu")
	{
		MainMenu mainmenu;
		this->window->close();
		mainmenu.run();
	}
}

void CreditsMenu::render_text_fields()
{
	this->window->draw(this->background);

	this->window->draw(*this->main_text);
	this->window->draw(*this->go_back);
}

void CreditsMenu::poll_events()
{
	sf::Event ev;
	//std::cout << string(this->target_text->getString()) << endl;


	while (this->window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Enter || ev.key.code == sf::Keyboard::Escape)
			{
				MainMenu mainMenu;
				this->window->close();
				mainMenu.run();
			}
			break;
		default:
			break;
		}
		mouse_update();
	}

}

void CreditsMenu::update()
{
	this->poll_events();


}

void CreditsMenu::render()
{
	this->window->clear(sf::Color::Black);
	this->render_text_fields();

	this->window->display();
}

CreditsMenu::~CreditsMenu()
{
}
