#ifndef Menu_H
#define Menu_H
#include "Button.h"
#include <map>
#include "../Consts.h"

class Menu
{
protected:
	sf::Font font_;
	bool is_menu_open_ = false;
	std::map<GameTypeEnum, Button> buttons_;
	virtual GameTypeEnum check_actions_(sf::RenderWindow &window){};
	void virtual draw_menu_(sf::RenderWindow& window){};
	void virtual genarate_menu_() {};
	void check_quit_(sf::RenderWindow& window);
public:
	virtual void open_menu(sf::RenderWindow& window);
};


#endif 
