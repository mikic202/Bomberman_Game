#ifndef Item_H
#define Item_H
#include <iostream>
#include <vector>


class Item
{
protected:
	std::string name_;
	std::vector<int> position_;
	void check_position_(std::vector<int> postion);
public:
	void set_name(std::string nem_name);
	std::string name();
	void set_position(std::vector<int> new_postion);
	std::vector<int> position();
};


#endif // !Item_H

