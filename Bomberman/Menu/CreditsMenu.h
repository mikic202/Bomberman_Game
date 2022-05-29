#pragma once
#include "Menu.h"
#include "MainMenu.h"
class CreditsMenu : public Menu
{
public:
	CreditsMenu();
	void clickedField(sf::Text* target_text) override;

	virtual void render_text_fields();
	void poll_events() override;


	void update() override;
	void render() override;

	~CreditsMenu();
private:
	sf::Text* go_back;
	sf::Text* main_text;
};



