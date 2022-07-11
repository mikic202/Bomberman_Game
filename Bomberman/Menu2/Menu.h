#ifndef Menu_H
#define Menu_H
#include "Button.h"
#include <map>

class Menu
{
protected:
	bool is_menu_open_ = false;
	std::map<int, Button> buttons_;
	virtual void check_buttons_(sf::RenderWindow &window){};
	void virtual draw_menu_(sf::RenderWindow& window){};
	void virtual genarate_menu_() {};
	void check_quit_(sf::RenderWindow& window);
public:
	virtual void open_menu(sf::RenderWindow& window);
};


#endif 
