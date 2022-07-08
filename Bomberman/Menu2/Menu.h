#ifndef Menu_H
#define Menu_H


class Menu
{
protected:
	bool is_menu_open_ = false;
	virtual void check_buttons_(){};
	void virtual draw_menu(){};
public:
	virtual void open_menu();
};


#endif 
