#pragma once
#include "Menu.h"
#include "CreditsMenu.h"
#include "ChooseModeMenu.h"
class MainMenu : public Menu
{
public:
	MainMenu();
	void clickedField(sf::Text* target_text) override;
	void update() override;

	// function to draw everything
	void render() override;


	virtual void render_text_fields();

	~MainMenu();
private:
	sf::Text* play_story;
	sf::Text* play_coop;
	sf::Text* play_versus;
	sf::Text* scores;
	sf::Text* credits;
	sf::Text* exit;
};

