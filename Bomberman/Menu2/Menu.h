#ifndef Menu_H
#define Menu_H
#include "Button.h"

class Menu
{
protected:
	bool is_menu_open_ = false;
	std::vector<Button> buttons;
	virtual void check_buttons_(){};
	void virtual draw_menu_(){};
	void virtual genarate_menu_() {};
public:
	virtual void open_menu();
};


#endif 
