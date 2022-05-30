#include "Menu.h"
#include "../Game/Game.h"
#include "MainMenu.h"
// Menu that will be displayed if ESCAPE button was pressed during game
class PauseMenu : public Menu
{
public:
	PauseMenu( char type, unsigned int saved_num=0);

	void clickedField(sf::Text* target_text) override;

	//void poll_events() override;


	~PauseMenu();
private:
	char type; 
	
	// number of saved game
	unsigned int saved_num;

	// game that contains this pause menu
	Game game;

};