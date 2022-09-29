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
	sf::Text title_text_;
	std::map<GameTypeEnum, Button> buttons_;
	virtual GameTypeEnum check_actions_(sf::RenderWindow& window);
	void virtual draw_menu_(sf::RenderWindow& window){};
	void virtual genarate_menu_() {};
	void check_quit_(sf::RenderWindow& window);
	void check_if_mouse_still_pressed_();
	void load_backgroun_image_();
	sf::Sprite background_sprite_;
	sf::Texture background_texture_;
	const std::string menu_background_path_;
public:
	virtual std::vector<GameTypeEnum> open_menu(sf::RenderWindow& window);
};


#endif 
