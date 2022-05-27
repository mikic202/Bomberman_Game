#pragma once
#include "Menu.h"
class ChooseGameMenu : public Menu
{
public:
	ChooseGameMenu();
	virtual void clickedField(sf::Text* target_text) override;


	~ChooseGameMenu();

private:
	
};

