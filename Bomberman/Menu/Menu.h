#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include "../Consts.h"
#include "../Exceptions/menus_exceptions.h"
#include <SFML/Graphics/Text.hpp>

class Menu
{
public:
	Menu();
	// menu_fields vector of text fields in menu; can't be changed after creating menu
	Menu(float width, float height, std::string name, std::vector<sf::Text*> menu_fields);
	
	Menu(sf::VideoMode video_mode, std::string name, std::vector<sf::Text*> menu_fields);

	// function to show window with menu until it is closed or 
	// selected option from text field
	void run();


	virtual void poll_events();

	virtual void update();

	// function to render menu window
	virtual void render();

	// function that checks if cursor is over the text field
	virtual bool mouse_over(sf::Text* text);

	virtual void mouse_update();

	// When arrow key up or button W is pressed then this function is called
	void move_up();

	// When arrow key down or button S is pressed then this function is called
	void move_down();

	// function that is called when text field is pressed
	virtual void clickedField(sf::Text* target_text) = 0;

	virtual ~Menu();

protected:
	void set_menu_fields(std::vector<sf::Text*> menu_fields);

	sf::Clock menu_clock;

	std::vector<sf::Text*> menu_fields;
	sf::RenderWindow* window;
	sf::Font font;
	
	sf::Text* bottom_menu_field;
	sf::Text* top_menu_field;
	sf::Text* target_text;
	sf::Texture background_texture;
	sf::Sprite background;

	bool is_menu_open = true;
};