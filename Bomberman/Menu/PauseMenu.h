#include "Menu.h"
#include "../Game/Game.h"
#include "MainMenu.h"
// Menu that will be displayed if ESCAPE button was pressed during game
class PauseMenu : public Menu
{
public:
	PauseMenu( char type, unsigned int saved_num=0);
	PauseMenu(char type, sf::RenderWindow& window, unsigned int saved_num = 0);
	void poll_events() override;

	void clickedField(sf::Text* target_text) {};

	// When menu field is clicked
	bool clickedMenuField(sf::Text* target_text);

	//void poll_events() override;

	void mouse_update() override;

	bool get_can_game_continue();

	void set_is_menu_open(bool value);

	~PauseMenu();
private:
	char type; 
	
	// number of saved game
	unsigned int saved_num;

	bool can_game_continue = true;

	// game that contains this pause menu
	Game game;

};